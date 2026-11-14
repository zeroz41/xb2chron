#ifndef GF_MSGUNK_1000050_H
#define GF_MSGUNK_1000050_H

#include "fw/Message.h"

namespace gf {

// message 0x1000050 (no name for it survives; 1.0.0's 0x100004C, the ids moved by 4):
// BattleCharacter::CreateElementalComboEffect sends it to the character's GfComEffectCaster to start the effect
// m_name names, and starts the timer of the effect handle the caster answers in m_handle. The field names are
// not the original's.
class MsgUnk_1000050 : public ::fw::Message {
public:
    MsgUnk_1000050() : fw::Message(0x1000050, 0x80), pad_8(0) {}

    unsigned int pad_8;  // the sender clears it; meaning unknown
    const char* m_name;  // the effect
    unsigned int m_handle;  // the started effect's handle (0: none), set by the receiver
};

}  // namespace gf

#endif
