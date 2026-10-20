#ifndef CLASSES_GF_GFCOMBEHAVIORPC_LISTENER_H
#define CLASSES_GF_GFCOMBEHAVIORPC_LISTENER_H

#include "classes/gf/GfComBehaviorPc.h"

namespace gf {
// table 0x7100B69430
class GfComBehaviorPc::Listener {
public:
    virtual void onWkStandbyLogout();  // slot 0
};
}  // namespace gf

#endif
