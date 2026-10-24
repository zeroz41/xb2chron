#ifndef GF_MSGUNK_1000058_H
#define GF_MSGUNK_1000058_H

#include "fw/Message.h"

namespace gf {

// message 0x1000058 (no name for it survives): GfGameTarget::notifyTarget sends it, with nothing after the header,
// to a new target of object type 5
class MsgUnk_1000058 : public ::fw::Message {
public:
    MsgUnk_1000058() : fw::Message(0x1000058, 0x80) {}
};

}  // namespace gf

#endif
