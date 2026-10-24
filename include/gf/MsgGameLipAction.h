#ifndef GF_MSGGAMELIPACTION_H
#define GF_MSGGAMELIPACTION_H

#include "fw/Message.h"

namespace gf {

// message 0x100002F (the name by StateFieldTalk::procMsgGameLipAction, which its recieveMessage hands it)
class MsgGameLipAction : public ::fw::Message {
public:
};

}  // namespace gf

#endif
