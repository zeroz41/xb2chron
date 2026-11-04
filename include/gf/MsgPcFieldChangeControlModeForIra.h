#ifndef GF_MSGPCFIELDCHANGECONTROLMODEFORIRA_H
#define GF_MSGPCFIELDCHANGECONTROLMODEFORIRA_H

#include "fw/Message.h"

namespace gf {

// message 0x100001C (new in 3.0.1; 1.0.0's 0x100001C, MsgPcFieldNotifyChangePlayerID, moved to 0x100001D). 2.0.0's
// symbols name it: its procMsgPcFieldChangeControlModeForIra (the same function, 0x438 bytes) takes it.
// GfComBehaviorPc::recieveMessage hands it to procMsgPcFieldChangeControlModeForIra, which switches the PC to mode 1
// (AI agent) or 0 (pad agent) like MsgPcFieldChangeControlMode. Its sender is not found yet.
class MsgPcFieldChangeControlModeForIra : public ::fw::Message {
public:
    int m_mode;  // (the name is not the original's)
};

}  // namespace gf

#endif
