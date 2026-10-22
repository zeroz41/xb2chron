#ifndef CLASSES_APPS_FRAMEWORKLAUNCHER_H
#define CLASSES_APPS_FRAMEWORKLAUNCHER_H

#include "classes/ml/IScnRender.h"
#include "classes/ml/IWorkBackground.h"
#include "classes/ml/WorkObj.h"

namespace ml { class Scn; }
namespace ml { enum SCNPRIO_CB : int; }

namespace apps {
// a base of apps::FrameworkLauncher no evidence names yet
class TUnk_B3A150 {
public:
    virtual ~TUnk_B3A150();
};
// a base of apps::FrameworkLauncher no evidence names yet
class TUnk_B3A170 {
public:
    virtual void setDebugPause(bool) = 0;
    virtual void stepDebugPause() = 0;
    virtual void isDebugPause() const = 0;
    virtual void resetApp() = 0;
};
// table 0x7100B3A008; base at 0x1B8 unknown (TUnk_B3A150), base at 0x1C0 unknown (TUnk_B3A170)
class FrameworkLauncher : public ::ml::WorkObj, public ::ml::IScnRender, public ::ml::IWorkBackground, public TUnk_B3A150, public TUnk_B3A170 {
public:
    virtual ~FrameworkLauncher();  // slot 0
    virtual void wkUpdate();  // slot 9
    virtual void wkTail();  // slot 12
    virtual bool wkStandbyLogin();  // slot 14
    virtual bool wkStandbyLogout();  // slot 15
    virtual void setDebugPause(bool);  // slot 17
    virtual void stepDebugPause();  // slot 18
    virtual void isDebugPause() const;  // slot 19
    virtual void resetApp();  // slot 20
    virtual void cbRenderAfter(ml::Scn*, ml::SCNPRIO_CB);  // slot 21
    virtual void rdkReaded(char const*, void*, int);  // slot 22
    virtual void bkgHomeMenu(bool);  // slot 23
};
}  // namespace apps

#endif
