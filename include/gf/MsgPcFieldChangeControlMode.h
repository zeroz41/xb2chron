#ifndef GF_MSGPCFIELDCHANGECONTROLMODE_H
#define GF_MSGPCFIELDCHANGECONTROLMODE_H

#include "fw/Message.h"

namespace gf {

// message 0x100001B (1.0.0's MsgPcFieldChangeControlMode: GfComBehaviorPc::recieveMessage hands it to
// procMsgPcFieldChangeControlMode): how a PC is controlled, GfGameMoverSwitcher::switchMover sends 0 to the new leader
// and 1 to the one it replaces
class MsgPcFieldChangeControlMode : public ::fw::Message {
public:
    MsgPcFieldChangeControlMode(int mode) : fw::Message(0x100001B, 0x40), m_mode(mode) {}

    int m_mode;  // (the name is not the original's)
};

}  // namespace gf

#endif
