#ifndef GF_MSGGAMELIPACTION_H
#define GF_MSGGAMELIPACTION_H

#include "fw/Message.h"

namespace gf {

// message 0x100002F (the name by StateFieldTalk::procMsgGameLipAction, which its recieveMessage hands it)
class MsgGameLipAction : public ::fw::Message {
public:
    // CharaPlayTalkAuto's destructor builds one to turn its lip animation off
    MsgGameLipAction() : fw::Message(0x100002F, 0x40) {}
    // StateFieldTalk::procMsgGameLipAction: 0 forces the lip animation on (LipSyncPlugin::m_forcePlay), 1 off
    // (the name is not the original's)
    int m_action;
};

}  // namespace gf

#endif
