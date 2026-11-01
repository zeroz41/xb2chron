#ifndef GF_MSGGAMETALKACTION_H
#define GF_MSGGAMETALKACTION_H

#include "fw/Message.h"

namespace gf {

// message 0x100002E (the name by StateFieldTalk::procMsgGameTalkAction, which its recieveMessage hands it)
class MsgGameTalkAction : public ::fw::Message {
public:
    // CharaPlayActionAuto's destructor builds one to put the character back to its talk motion
    MsgGameTalkAction() : fw::Message(0x100002E, 0x40) {}
    // the talk motion: 0-2 the talk states S_talkA_00-02 (0 and 2 try their command first), 3 S_idle (the names
    // are not the original's)
    unsigned int m_action;
    bool m_setState;  // set: the state is set straight away, no command tried
    bool m_result;    // the handler's answer: whether the motion was set
};

}  // namespace gf

#endif
