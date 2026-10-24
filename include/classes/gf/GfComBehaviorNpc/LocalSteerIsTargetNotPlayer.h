#ifndef CLASSES_GF_GFCOMBEHAVIORNPC_LOCALSTEERISTARGETNOTPLAYER_H
#define CLASSES_GF_GFCOMBEHAVIORNPC_LOCALSTEERISTARGETNOTPLAYER_H

#include "classes/gf/GfComBehaviorNpc.h"

namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GfFieldLocalSteer; }

namespace gf {
// table 0x7100B668D0
class GfComBehaviorNpc::LocalSteerIsTargetNotPlayer {
public:
    // whether the target the steering considers is not the party leader
    virtual bool operator()(gf::GfFieldLocalSteer const& steer, gf::GF_OBJ_HANDLE* target) const;  // slot 0
};
}  // namespace gf

#endif
