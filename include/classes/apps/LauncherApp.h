#ifndef CLASSES_APPS_LAUNCHERAPP_H
#define CLASSES_APPS_LAUNCHERAPP_H

#include "classes/ml/WinProc.h"
#include "classes/apps/FrameworkLauncher.h"

namespace ml { class EventButton; }
namespace ml { class EventFileTh; }
namespace ml { class EventFloatingMenu; }
namespace ml { class EventView; }
namespace ml { enum CPUID : int; }

namespace apps {
// a base of apps::LauncherApp no evidence names yet
class TUnk_B3A318 {
public:
    virtual ~TUnk_B3A318();
    virtual void vf2();
};
// table 0x7100B3A258; base at 0x0 ml::WinProc (its destructor stores WinProc's table), base at 0x1F0 unknown (TUnk_B3A318)
class LauncherApp : public ::ml::WinProc, public TUnk_B3A318 {
public:
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
    unsigned char pad_1F8[0x609 - 0x1F8];
    // 0x609: a closing FrameworkLauncher handed it m_appletParam (the launcher's destructor sets it, then sends
    // event 0; the name is not the original's)
    bool m_appletPending;
    unsigned char pad_60a[0x6];
    FrameworkLauncher::AppletCreateParam m_appletParam;  // 0x610 the closing launcher's copy (the name is not the original's)
};
}  // namespace apps

#endif
