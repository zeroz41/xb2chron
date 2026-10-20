#ifndef CLASSES_GF_GFCOMBEHAVIORENEMY_LISTENER_H
#define CLASSES_GF_GFCOMBEHAVIORENEMY_LISTENER_H

#include "classes/gf/GfComBehaviorEnemy.h"

namespace gf {
// table 0x7100B65F28
class GfComBehaviorEnemy::Listener {
public:
    virtual void onWkStandbyLogout();  // slot 0
};
}  // namespace gf

#endif
