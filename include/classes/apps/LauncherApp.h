#ifndef CLASSES_APPS_LAUNCHERAPP_H
#define CLASSES_APPS_LAUNCHERAPP_H

#include "classes/ml/WorkObj.h"

namespace ml { class EventButton; }
namespace ml { class EventFileTh; }
namespace ml { class EventFloatingMenu; }
namespace ml { class EventView; }
namespace ml { enum CPUID : int; }

namespace apps {
// between apps::LauncherApp and ml::WorkObj: fields, no virtuals of its own
class TUnk_B3A258 : public ::ml::WorkObj {
public:
    unsigned char pad_1A8[0x48];  // fields: size from its derived classes
};
// a base of apps::LauncherApp no evidence names yet
class TUnk_B3A318 {
public:
    virtual ~TUnk_B3A318();
    virtual void vf2();
};
// table 0x7100B3A258; base at 0x0 unknown (TUnk_B3A258), base at 0x1F0 unknown (TUnk_B3A318)
class LauncherApp : public TUnk_B3A258, public TUnk_B3A318 {
public:
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
    virtual void OnMouseButtonDown(ml::EventView*);  // slot 17
    virtual void OnKeyDown(ml::EventView*);  // slot 18
    virtual void OnFMenuSelect(ml::EventFloatingMenu*);  // slot 19
    virtual void OnCButtonSelect(ml::EventButton*);  // slot 20
    virtual void errcbCallback(ml::CPUID, unsigned long);  // slot 21
    unsigned char pad_1F8[0x568];  // fields: size from its derived classes
};
}  // namespace apps

#endif
