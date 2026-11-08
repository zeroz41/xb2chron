#ifndef CLASSES_APPS_FRAMEWORKLAUNCHER_H
#define CLASSES_APPS_FRAMEWORKLAUNCHER_H

#include "classes/ml/IScnRender.h"
#include "classes/ml/IWorkBackground.h"
#include "classes/ml/WorkObj.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "fw/FrameworkConfig.h"
#include "ml/ScnSetup.h"
#include "mm/Rect.h"

namespace apps { class FrameworkLauncher; }
namespace ml { class Scn; }
namespace ml { class WinView; }
namespace ml { enum SCNPRIO_CB : int; }
namespace ml { class MLTHG; }
namespace ml { class MLTH; }
namespace nn { namespace os { class FiberType; }}
namespace ml { class WinProc; }

namespace apps {
// what the launcher builds its view and scene from (createBuildThread's second; the launcher keeps a copy at 0x240,
// its AppletCreateParam another at 0x98). Only what the build thread reads has names; none is the original's.
class SceneBuildInfo {
public:
    SceneBuildInfo() : m_flags(0x7e), m_viewPriority(0x40) {}

    // 0x00 the build thread tests 0x1 (m_viewRect applies), 0x10, 0x20, 0x40 (the render system's toon light scale,
    // tone map, toon ambient), 0x80 (no motion blur), 0x100 (no camera light), 0x200 (no auto reduction)
    unsigned int m_flags;
    ml::ScnSetup m_scnSetup;  // 0x08 the scene's setup
    mm::Rect<int> m_viewRect;  // 0x50 copied to the view when m_flags 0x1 is set
    int m_viewPriority;  // 0x60 WinProc::pssCreateView's fourth
};
}  // namespace apps

namespace apps {
// a base of apps::FrameworkLauncher no evidence names yet
class TUnk_B3A170 {
public:
    virtual void setDebugPause(bool) = 0;
    virtual void stepDebugPause() = 0;
    virtual bool isDebugPause() const = 0;
    virtual bool resetApp() = 0;
};
// table 0x7100B3A008; base at 0x1B8 PtrSingleton<FrameworkLauncher> (its table 0x7100B3A150 holds only the destructor thunks; ~PtrSingleton stores 0x7100B3A218; getScn reads sys() at 0x2B8), base at 0x1C0 unknown (TUnk_B3A170)
class FrameworkLauncher : public ::ml::WorkObj, public ::ml::IScnRender, public ::ml::IWorkBackground, public ::mm::mtl::PtrSingleton< ::apps::FrameworkLauncher>, public TUnk_B3A170 {
public:
    virtual ~FrameworkLauncher();  // slot 0
    virtual void wkUpdate();  // slot 9
    virtual void wkTail();  // slot 12
    virtual bool wkStandbyLogin();  // slot 14
    virtual bool wkStandbyLogout();  // slot 15
    virtual void setDebugPause(bool);  // slot 17
    virtual void stepDebugPause();  // slot 18
    virtual bool isDebugPause() const;  // slot 19
    virtual bool resetApp();  // slot 20
    virtual void cbRenderAfter(ml::Scn*, ml::SCNPRIO_CB);  // slot 21
    virtual void rdkReaded(char const*, void*, int);  // slot 22
    virtual void bkgHomeMenu(bool);  // slot 23
    // what an applet is created from; the launcher hands its copy to its parent LauncherApp when it closes.
    // Its fields are only known from the copy assignment: 0x8 a FixStr<128>, 0xB0 a FixStr<32>, 0x100 0x50 bytes
    // copied whole.
    class AppletCreateParam {
    public:
        AppletCreateParam() : m_create(nullptr), m_proc(nullptr), m_onBuilt(nullptr), m_onTerminated(nullptr) {}

        // what create<T> stores in m_create: it makes the applet again from the same parameters (2.0.0's symbols
        // name createFunctor<tl::TitleApplet>::create)
        template <class T>
        class createFunctor {
        public:
            static bool create(ml::WinProc* proc, SceneBuildInfo& info, const fw::FrameworkConfig& config,
                               void (*onBuilt)(), void (*onTerminated)()) {
                return FrameworkLauncher::create<T>(proc, info, config, onBuilt, onTerminated);
            }
        };

        // 0x00 createFunctor<T>::create of the applet type create<T> made (the name is not the original's)
        bool (*m_create)(ml::WinProc*, SceneBuildInfo&, const fw::FrameworkConfig&, void (*)(), void (*)());
        mm::mtl::FixStr<128> m_name;  // 0x08 (the name is not the original's)
        ml::WinProc* m_proc;  // 0x90 create<T>'s proc (the name is not the original's)
        SceneBuildInfo m_buildInfo;  // 0x98 (the name is not the original's)
        fw::FrameworkConfig m_config;  // 0x100 (the name is not the original's)
        void (*m_onBuilt)();  // 0x140 (createBuildThread's fourth; the name is not the original's)
        void (*m_onTerminated)();  // 0x148 (createBuildThread's fifth; the name is not the original's)
    };
    // the launcher's scene and view (PtrSingleton<FrameworkLauncher>'s), none without a launcher
    static ml::Scn* getScn();
    static ml::WinView* getView();
    // asks the launcher to close: true once it is closed (or there is none)
    static bool destroy();
    static nn::os::FiberType* mlthFnTermUpdate(void* launcher);
    // draws the launcher's scene while the main view is the launcher's
    static void drawTask();
    void update();
    FrameworkLauncher(const char* name, ml::WorkObj* parent);
    // makes the launcher under proc (once) and starts its build thread: true once the build is done
    static bool createBuildThread(ml::WinProc* proc, SceneBuildInfo& info, const fw::FrameworkConfig& config,
                                  void (*onBuilt)(), void (*onTerminated)());
    static nn::os::FiberType* mlthFnBuild(void* launcher);
    // starts the thread that waits for the resources: true once they are loaded
    static bool createWaitLoadResourceThread();
    static nn::os::FiberType* mlthFnLoadResource(void* launcher);
    // starts the thread that initializes the applet: true once it is initialized
    static bool createAppletInitializeThread();
    static nn::os::FiberType* mlthFnAppletInitialize(void* launcher);
    // the launcher's steps for an applet of type T, one per call (tl::TitleApp::wkStandbyLogin calls it until it is
    // true): build the scene, create the applet on the framework, load its resources, initialize it; then keeps the
    // parameters in m_appletParam (2.0.0's symbols name create<tl::TitleApplet>)
    template <class T>
    static bool create(ml::WinProc* proc, SceneBuildInfo& info, const fw::FrameworkConfig& config, void (*onBuilt)(),
                       void (*onTerminated)());

    // 0x1C8: request bits: stepDebugPause sets 0x200000, resetApp sets 0x50000000 unless one of 0x70000000 is set;
    // wkTail skips the framework's tail while 0x90 is set; 0x10: closed (destroy); 0x20000000 destroy started the
    // terminating thread; 0x40000000: the destructor hands the applet parameters to the parent (the name is not the
    // original's)
    unsigned int m_request;
    // 0x1CC the work id of the process createBuildThread made the launcher under (WorkObj 0x50), -1 none (the name
    // is not the original's)
    unsigned int m_procWid;
    // 0x1D0, 0x1D8: micro thread groups: wkUpdate updates the first, wkTail the second, the destructor releases both
    // (the names are not the original's)
    ml::MLTHG* m_updateGroup;
    ml::MLTHG* m_tailGroup;
    // 0x1E0: the threads; destroy starts mlthFnTermUpdate in the first only while all four are -1 (the name is not
    // the original's)
    ml::MLTH* m_threads[4];
    fw::FrameworkConfig m_config;  // 0x200 createBuildThread's copy (the name is not the original's)
    SceneBuildInfo m_buildInfo;    // 0x240 createBuildThread's copy (the name is not the original's)
    // 0x2A8 called once the framework's managers are initialized; 0x2B0 once they are finalized (createBuildThread's
    // fourth and fifth; the names are not the original's)
    void (*m_onBuilt)();
    void (*m_onTerminated)();
    ml::Scn* m_scn;       // 0x2B8 getScn (the name is not the original's)
    ml::WinView* m_view;  // 0x2C0 getView (the name is not the original's)
    AppletCreateParam m_appletParam;  // 0x2C8 the destructor's copy to LauncherApp (the name is not the original's)
    // 0x418: the home menu is up (bkgHomeMenu): wkUpdate and wkTail do nothing (the name is not the original's)
    bool m_homeMenu;
    // 0x419: stepDebugPause requests a step only while it is set (the name is not the original's)
    bool m_debugPauseStepOk;
    bool m_debugPause;  // 0x41A isDebugPause (the name is not the original's)
    // the rest of the launcher is not known yet
};
}  // namespace apps

#include "classes/fw/Framework.h"
#include "classes/fw/Applet.h"
#include "classes/mm/mtl/IAllocator.h"

namespace apps {
template <class T>
bool FrameworkLauncher::create(ml::WinProc* proc, SceneBuildInfo& info, const fw::FrameworkConfig& config,
                               void (*onBuilt)(), void (*onTerminated)()) {
    if (!createBuildThread(proc, info, config, onBuilt, onTerminated)) {
        return false;
    }
    FrameworkLauncher* launcher = get();
    if (!(launcher->m_request & 0x200)) {
        launcher->m_request |= 0x200;
        fw::Framework* framework = fw::Framework::get();
#line 175 "D:/Monolithsoft/BF2/prog/application/BF2\\framework/framework.h"
        T* applet = new (fw::Framework::getAllocator(), 8, __FILE__, __LINE__) T();
        framework->m_applet = applet;
        applet->m_env.m_view = framework->m_view;
        applet->m_env.m_scn = framework->m_scn;
        applet->m_env.pad_0 = framework->pad_50;
        applet->m_env.m_memHandle = framework->m_memHandle;
        applet->m_env.pad_20 = framework->pad_70;
        return false;
    }
    if (launcher->m_request & 0x800) {
        if (!createAppletInitializeThread()) {
            return false;
        }
    } else {
        if (!createWaitLoadResourceThread()) {
            return false;
        }
    }
    launcher = get();
    launcher->m_appletParam.m_name = "ResetAppret";
    launcher->m_appletParam.m_create = &AppletCreateParam::createFunctor<T>::create;
    launcher->m_appletParam.m_proc = proc;
    launcher->m_appletParam.m_buildInfo = info;
    launcher->m_appletParam.m_config = config;
    launcher->m_appletParam.m_onBuilt = onBuilt;
    launcher->m_appletParam.m_onTerminated = onTerminated;
    return true;
}
}  // namespace apps

#endif
