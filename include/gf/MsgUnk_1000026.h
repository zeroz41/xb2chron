#ifndef GF_MSGUNK_1000026_H
#define GF_MSGUNK_1000026_H

#include "fw/Message.h"

namespace gf {

// message 0x1000026 (no name for it survives): StateField::onDead sends it to the buddy when the PC dies outright
// (dead type 4) in the field
class MsgUnk_1000026 : public ::fw::Message {
public:
    MsgUnk_1000026() : fw::Message(0x1000026, 0x40) {}
};

}  // namespace gf

#endif
