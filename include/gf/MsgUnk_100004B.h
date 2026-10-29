#ifndef GF_MSGUNK_100004B_H
#define GF_MSGUNK_100004B_H

#include "fw/Message.h"

namespace gf {

// message 0x100004B (no name for it survives; category 0x400, no payload): GfComBehaviorPc::onWarpNormal sends it to
// the PC's object after a warp
class MsgUnk_100004B : public ::fw::Message {
public:
    MsgUnk_100004B() : fw::Message(0x100004B, 0x400) {}
};

}  // namespace gf

#endif
