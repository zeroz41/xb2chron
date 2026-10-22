#ifndef GF_MSGPCFIELDHIGHJUMP_H
#define GF_MSGPCFIELDHIGHJUMP_H

#include "fw/Message.h"

namespace gf {

// message 0x1000016 (1.0.0's MsgPcFieldHighJump, by the handler that takes it): asks a PC to act on AIAgentField's
// high jump notice (MsgPcFieldNotifyHighJump, 0x1000015); StateFieldIdle::procMsgPcFieldHighJump accepts it
class MsgPcFieldHighJump : public ::fw::Message {
public:
    MsgPcFieldHighJump() : fw::Message(0x1000016, 0x40), m_accepted(false) {}

    bool m_accepted;  // the handler's answer (the name is not the original's)
};

}  // namespace gf

#endif
