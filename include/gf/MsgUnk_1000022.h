#ifndef GF_MSGUNK_1000022_H
#define GF_MSGUNK_1000022_H

#include "fw/Message.h"

namespace gf {

// message 0x1000022 (no name for it survives; GfComBehaviorExtra::recieveMessage answers it by playing
// "C_schedule_00_00"): StateUtilField::notifyJumpEnd sends it to the objects mounted on the PC
class MsgUnk_1000022 : public ::fw::Message {
public:
    MsgUnk_1000022() : fw::Message(0x1000022, 0x40), m_value(0) {}

    int m_value;  // 0 from notifyJumpEnd (meaning not known; the name is not the original's)
};

}  // namespace gf

#endif
