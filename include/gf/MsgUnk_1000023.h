#ifndef GF_MSGUNK_1000023_H
#define GF_MSGUNK_1000023_H

#include "fw/Message.h"

namespace gf {

// message 0x1000023 (no name for it survives; 1.0.0 sends the same message as 0x1000022, which
// GfComBehaviorExtra::recieveMessage answers by playing "C_schedule_00_00"): GfGamePlayerUniqueScheduler::update sends
// it to a party member whose wait ran out, with the motion (0 to 2) the member is to play
class MsgUnk_1000023 : public ::fw::Message {
public:
    explicit MsgUnk_1000023(unsigned int motion) : fw::Message(0x1000023, 0x40), m_motion(motion), m_flag(false) {}

    unsigned int m_motion;  // the name is not the original's
    bool m_flag;            // the sender clears it (meaning not known)
};

}  // namespace gf

#endif
