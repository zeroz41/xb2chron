#ifndef GF_MSGUNK_100001C_H
#define GF_MSGUNK_100001C_H

#include "fw/Message.h"

namespace gf {

// message 0x100001C (new in 3.0.1, no name for it survives; 1.0.0's 0x100001C, MsgPcFieldNotifyChangePlayerID, moved
// to 0x100001D): GfComBehaviorPc::recieveMessage hands it to fn_710050EF90, which switches the PC to mode 1 (AI
// agent) or 0 (pad agent) like MsgPcFieldChangeControlMode. Its sender is not found yet, so its category is unknown.
class MsgUnk_100001C : public ::fw::Message {
public:
    int m_mode;  // (the name is not the original's)
};

}  // namespace gf

#endif
