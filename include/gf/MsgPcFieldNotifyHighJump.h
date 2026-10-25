#ifndef GF_MSGPCFIELDNOTIFYHIGHJUMP_H
#define GF_MSGPCFIELDNOTIFYHIGHJUMP_H

#include "fw/Message.h"

namespace gf {
class MsgPcFieldNotifyBigJump;

// message 0x1000015 (the name by 1.0.0's GfComBehaviorPc::procMsgPcFieldNotifyHighJump, which reads the pointer at
// +8; 1.0.0's StateFieldPrepareBigJump::procMsgPcFieldNotifyBigJump sends 0x1000015 too): the PC's big jump notice,
// StateFieldPrepareBigJump::procMsgPcFieldNotifyBigJump broadcasts it to the party with the jump it takes
class MsgPcFieldNotifyHighJump : public ::fw::Message {
public:
    explicit MsgPcFieldNotifyHighJump(const MsgPcFieldNotifyBigJump* jump) : fw::Message(0x1000015, 0x40), m_jump(jump) {}
    const MsgPcFieldNotifyBigJump* m_jump;  // (the name is not the original's)
};
}  // namespace gf

#endif
