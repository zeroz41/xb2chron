#ifndef CLASSES_APPS_FRAMEWORKLAUNCHER_H
#define CLASSES_APPS_FRAMEWORKLAUNCHER_H

#include "classes/ml/IScnRender.h"
#include "classes/ml/IWorkBackground.h"
#include "classes/ml/WorkObj.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace apps { class FrameworkLauncher; }
namespace ml { class Scn; }
namespace ml { class WinView; }
namespace ml { enum SCNPRIO_CB : int; }

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
    // the launcher's scene and view (PtrSingleton<FrameworkLauncher>'s), none without a launcher
    static ml::Scn* getScn();
    static ml::WinView* getView();

    // 0x1C8: request bits: stepDebugPause sets 0x200000, resetApp sets 0x50000000 unless one of 0x70000000 is set;
    // wkTail skips the framework's tail while 0x90 is set (the name is not the original's)
    unsigned int m_request;
    unsigned char pad_1cc[0x2b8 - 0x1cc];
    ml::Scn* m_scn;       // 0x2B8 getScn (the name is not the original's)
    ml::WinView* m_view;  // 0x2C0 getView (the name is not the original's)
    unsigned char pad_2c8[0x419 - 0x2c8];
    // 0x419: stepDebugPause requests a step only while it is set (the name is not the original's)
    bool m_debugPauseStepOk;
    bool m_debugPause;  // 0x41A isDebugPause (the name is not the original's)
    // the rest of the launcher is not known yet
};
}  // namespace apps

#endif
