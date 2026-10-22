#ifndef GF_MSGPCFIELDWALLJUMP_H
#define GF_MSGPCFIELDWALLJUMP_H

#include "fw/Message.h"

namespace gf {

// message 0x1000013 (in 1.0.0 too; 1.0.0's StateFieldOnWall::procMsgPcFieldWallJump names it): asks a PC on a
// wall to jump; TaskFieldWallJumpWait::update sends it once no other player is in the way
class MsgPcFieldWallJump : public ::fw::Message {
public:
    MsgPcFieldWallJump() : fw::Message(0x1000013, 0x40), m_accepted(false) {}

    bool m_accepted;  // set by the state that takes it (the name is not the original's)
};

}  // namespace gf

#endif
