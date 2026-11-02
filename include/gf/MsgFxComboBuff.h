#ifndef GF_MSGFXCOMBOBUFF_H
#define GF_MSGFXCOMBOBUFF_H

#include "fw/Message.h"

namespace gf {

// message 0x1000051: 1.0.0's GfComEffectCaster::procMsgFxComboBuff(fw::MessageObject*, gf::MsgFxComboBuff&) names
// it (1.0.0's id 0x100004D, the ids moved by 4 as MsgFxWeapon's 0x1000050 -> 0x1000054); the caster starts the
// effect m_name names. BattleCharacter::CreateElementalEffect sends it. The field names are not the original's.
class MsgFxComboBuff : public ::fw::Message {
public:
    MsgFxComboBuff() : fw::Message(0x1000051, 0x80), pad_8(0) {}

    unsigned int pad_8;  // the sender clears it; meaning unknown
    const char* m_name;  // the effect (procMsgFxComboBuff reads it)
};

}  // namespace gf

#endif
