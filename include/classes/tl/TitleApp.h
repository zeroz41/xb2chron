#ifndef CLASSES_TL_TITLEAPP_H
#define CLASSES_TL_TITLEAPP_H

#include "classes/apps/LauncherApp.h"

namespace tl {
// a base of tl::TitleApp no evidence names yet
class TUnk_B3FF78 {
public:
    virtual ~TUnk_B3FF78();
};
// table 0x7100B3FE90; base at 0x760 unknown (TUnk_B3FF78)
class TitleApp : public ::apps::LauncherApp, public TUnk_B3FF78 {
public:
    virtual ~TitleApp();  // slot 0
    virtual bool wkStandbyLogin();  // slot 14
    virtual bool wkStandbyLogout();  // slot 15
};
}  // namespace tl

#endif
