#ifndef GF_MSGUNK_100000A_H
#define GF_MSGUNK_100000A_H

#include "fw/Message.h"

namespace gf {

// message 0x100000A (no name for it survives; 1.0.0's GfComBehaviorPc::recieveMessage has no case for it):
// GfGameRide::procMsgGameRideEvent sends it with 0 to the leader driver after it gets down
class MsgUnk_100000A : public ::fw::Message {
public:
    explicit MsgUnk_100000A(int value) : fw::Message(0x100000A, 0x40), m_value(value) {}

    int m_value;
    unsigned char pad_c[0xC];  // not set by the sender: the stack object is 0x18 bytes
};

}  // namespace gf

#endif
