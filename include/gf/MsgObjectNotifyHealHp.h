#ifndef GF_MSGOBJECTNOTIFYHEALHP_H
#define GF_MSGOBJECTNOTIFYHEALHP_H

#include "fw/Message.h"

namespace gf { class MsgObjectHealHp; }

namespace gf {

// message 0x100003C (1.0.0's MsgObjectNotifyHealHp, by StateFieldWaterDead::procMsgObjectNotifyHealHp that takes
// it; 1.0.0's id is 0x1000039): an object's HP healed
class MsgObjectNotifyHealHp : public ::fw::Message {
public:
    // StateFieldWaterDeadIdle sends itself one (inline: its code has it)
    MsgObjectNotifyHealHp() : fw::Message(0x100003C, 0x40), m_heal(nullptr), m_healType(0) {}

    // the heal it reports (GfComProperty::procMsgObjectHealHp's; the name is not the original's)
    const gf::MsgObjectHealHp* m_heal;
    // the hit points before the heal (GfComProperty::procMsgObjectHealHp's): StateFieldWaterDead revives the PC only
    // when it is 0 (the name is not the original's)
    int m_healType;
};

}  // namespace gf

#endif
