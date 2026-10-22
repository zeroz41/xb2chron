#ifndef GF_MSGPCFIELDNOTIFYCHANGEPLAYERID_H
#define GF_MSGPCFIELDNOTIFYCHANGEPLAYERID_H

#include "fw/Message.h"

namespace gf {

// message 0x100001D (1.0.0's MsgPcFieldNotifyChangePlayerID, 0x100001C there: GfGamePlayerFormation::swapFormation
// sends it in both, and GfComPropertyPc::procMsgPcFieldNotifyChangePlayerID keeps its index): a PC's new player index
class MsgPcFieldNotifyChangePlayerID : public ::fw::Message {
public:
    MsgPcFieldNotifyChangePlayerID(unsigned int playerID) : fw::Message(0x100001D, 0x20), m_playerID(playerID) {}

    unsigned int m_playerID;
};

}  // namespace gf

#endif
