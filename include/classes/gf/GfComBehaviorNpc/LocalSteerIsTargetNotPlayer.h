#ifndef CLASSES_GF_GFCOMBEHAVIORNPC_LOCALSTEERISTARGETNOTPLAYER_H
#define CLASSES_GF_GFCOMBEHAVIORNPC_LOCALSTEERISTARGETNOTPLAYER_H

#include "classes/gf/GfComBehaviorNpc.h"

namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GfFieldLocalSteer; }

namespace gf {
// table 0x7100B668D0
class GfComBehaviorNpc::LocalSteerIsTargetNotPlayer {
public:
    virtual void operator()(gf::GfFieldLocalSteer const&, gf::GF_OBJ_HANDLE*) const;  // slot 0
};
}  // namespace gf

#endif
