#ifndef GF_MSGOBJECTNOTIFYHEALHP_H
#define GF_MSGOBJECTNOTIFYHEALHP_H

#include "fw/Message.h"

namespace gf {

// message 0x100003C (1.0.0's MsgObjectNotifyHealHp, by StateFieldWaterDead::procMsgObjectNotifyHealHp that takes
// it; 1.0.0's id is 0x1000039): an object's HP healed
class MsgObjectNotifyHealHp : public ::fw::Message {
public:
    // StateFieldWaterDeadIdle sends itself one (inline: its code has it)
    MsgObjectNotifyHealHp() : fw::Message(0x100003C, 0x40), pad_8(), m_healType(0) {}

    unsigned char pad_8[0x8];
    // StateFieldWaterDead revives the PC only when it is 0 (meaning not known yet; the name is not the original's)
    int m_healType;
};

}  // namespace gf

#endif
