#ifndef CLASSES_APPS_LAUNCHERAPP_H
#define CLASSES_APPS_LAUNCHERAPP_H

#include "classes/ml/WinProc.h"
#include "classes/apps/FrameworkLauncher.h"
#include "classes/ml/IErrorCB.h"
#include "mm/mtl/FixedVector.h"

namespace ml { class EventButton; }
namespace ml { class EventFileTh; }
namespace ml { class EventFloatingMenu; }
namespace ml { class EventView; }
namespace ml { enum CPUID : int; }
namespace ml { class Scn; }
namespace ml { class WinView; }

namespace apps {
// table 0x7100B3A258; base at 0x0 ml::WinProc (its destructor stores WinProc's table), base at 0x1F0 ml::IErrorCB
// (the constructor hands it to WorkCpu::registErrorCB, the destructor to unregistErrorCB; its table holds
// errcbCallback's thunk)
class LauncherApp : public ::ml::WinProc, public ::ml::IErrorCB {
public:
    // what the second vector holds: wkRender calls slot 2 with the app, the launcher's scene and view while
    // m_debugInfo is set, destroyDebugDraw deletes them (the class name and draw are not the original's)
    class DebugDraw {
    public:
        virtual ~DebugDraw() {}  // slot 0
        virtual void draw(LauncherApp*, ml::Scn*, ml::WinView*) = 0;  // slot 2
    };

    LauncherApp(const char* name, ml::WorkObj* parent, int childCapacity);
    virtual ~LauncherApp();  // slot 0
    virtual void OnSystemPause(unsigned int);  // slot 2
    virtual void OnShutdownForce();  // slot 3
    virtual void OnPauseTrigger(bool, char const*);  // slot 5
    virtual void OnViewResize(ml::EventView*);  // slot 6
    virtual bool OnFileEvent(ml::EventFileTh*);  // slot 7
    virtual void wkUpdate();  // slot 9
    virtual void wkRender();  // slot 10
    virtual void wkTail();  // slot 12
    virtual bool wkStandbyLogin() = 0;  // slot 14
    virtual bool wkStandbyLogout();  // slot 15
    virtual bool OnMouseButtonDown(ml::EventView*);  // slot 17
    virtual bool OnKeyDown(ml::EventView*);  // slot 18
    virtual bool OnFMenuSelect(ml::EventFloatingMenu*);  // slot 19
    virtual bool OnCButtonSelect(ml::EventButton*);  // slot 20
    virtual void errcbCallback(ml::CPUID, unsigned long);  // slot 21
    // 1.0.0's destroyMenu and destroyDebugDraw (3.0.1 inlines them into the destructor): delete every element
    // the vector holds, then empty it
    void destroyMenu() {
        for (ml::IWorkEvent** it = m_menus.begin(); it != m_menus.end(); ++it) {
            delete *it;
        }
        m_menus.clear();
    }
    void destroyDebugDraw() {
        for (DebugDraw** it = m_debugDraws.begin(); it != m_debugDraws.end(); ++it) {
            delete *it;
        }
        m_debugDraws.clear();
    }

    // 0x1F8 OnFileEvent offers the event to each after the applet; destroyMenu deletes them (the name is not the
    // original's; their slot 1 is a deleting destructor, slot 7 OnFileEvent as ml::IWorkEvent's)
    mm::mtl::FixedVector<ml::IWorkEvent*, 64> m_menus;
    mm::mtl::FixedVector<DebugDraw*, 64> m_debugDraws;  // 0x400 (destroyDebugDraw; the name is not the original's)
    // 0x608 true from the constructor; wkRender draws m_debugDraws while set (1.0.0's isDebugInfo/setDebugInfo read
    // and write it; the name is not the original's)
    bool m_debugInfo;
    // 0x609: a closing FrameworkLauncher handed it m_appletParam (the launcher's destructor sets it, then sends
    // event 0; the name is not the original's)
    bool m_appletPending;
    unsigned char pad_60a[0x6];
    FrameworkLauncher::AppletCreateParam m_appletParam;  // 0x610 the closing launcher's copy (the name is not the original's)
};
}  // namespace apps

#endif
