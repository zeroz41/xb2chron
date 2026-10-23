#ifndef CLASSES_GF_GFCOMBEHAVIORMOB_LISTENER_H
#define CLASSES_GF_GFCOMBEHAVIORMOB_LISTENER_H

#include "classes/gf/GfComBehaviorMob.h"

namespace gf {
// table 0x7100B66570
class GfComBehaviorMob::Listener {
public:
    virtual void onWkStandbyLogout();  // slot 0
    GfComBehaviorMob* m_owner;  // the behavior it listens for (the name is not the original's)
};
}  // namespace gf

#endif
