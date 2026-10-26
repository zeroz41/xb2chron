#ifndef GF_MSGFXFOOTPRINT_H
#define GF_MSGFXFOOTPRINT_H

#include "fw/Message.h"

namespace gf {

// a foot touched the ground: the effect caster emits the ground's foot step effect
// (GfEffectGround::emitFootStepEffect). The field names are not the original's.
class MsgFxFootPrint : public ::fw::Message {
public:
    // which ground (1.0.0's FootStepPlugin::emissionEffect stores its GfEnvProperty::GROUND_INDEX here)
    int m_groundIndex;
    // 1.0.0's FootStepPlugin::emissionEffect copies its byte at 0x9 here; emitFootStepEffect then emits effect
    // kind 3 instead of 2
    bool m_alternate;
};

}  // namespace gf

#endif
