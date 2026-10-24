#ifndef GF_MSGUNK_100001A_H
#define GF_MSGUNK_100001A_H

#include "fw/Message.h"

namespace gf {

// message 0x100001A (no name for it survives): StateFieldTalk::onLeave broadcasts it to the party when a talk ends
class MsgUnk_100001A : public ::fw::Message {
public:
    MsgUnk_100001A() : fw::Message(0x100001A, 0x20) {}
};

}  // namespace gf

#endif
