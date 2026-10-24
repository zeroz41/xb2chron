#ifndef GF_MSGPCFIELDRELAYSURVIVE_H
#define GF_MSGPCFIELDRELAYSURVIVE_H

#include "fw/Message.h"

namespace gf {

// message 0x100001F (1.0.0's MsgPcFieldRelaySurvive, by the water states' procMsgPcFieldRelaySurvive that take it;
// 1.0.0's id is 0x100001E): a death or revival the PC hands its buddy (StateUtil::sendMessageToBuddy); the buddy's
// water states act on the message it carries
class MsgPcFieldRelaySurvive : public ::fw::Message {
public:
    explicit MsgPcFieldRelaySurvive(fw::Message* msg) : fw::Message(0x100001F, 0x40), m_msg(msg) {}
    fw::Message* m_msg;  // the message relayed: a MsgObjectNotifyDead or MsgObjectNotifyHealHp (the name is not the original's)
};

}  // namespace gf

#endif
