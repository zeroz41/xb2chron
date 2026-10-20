#ifndef CLASSES_GF_GFCOMBEHAVIORNPC_LISTENER_H
#define CLASSES_GF_GFCOMBEHAVIORNPC_LISTENER_H

#include "classes/gf/GfComBehaviorNpc.h"

namespace gf {
// table 0x7100B668E8
class GfComBehaviorNpc::Listener {
public:
    virtual void onWkStandbyLogout();  // slot 0
};
}  // namespace gf

#endif
