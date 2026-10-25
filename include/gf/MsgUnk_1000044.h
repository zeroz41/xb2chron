#ifndef GF_MSGUNK_1000044_H
#define GF_MSGUNK_1000044_H

#include "fw/Message.h"

namespace gf {

// message 0x1000044 (no name for it survives; 1.0.0's StateFieldLure::update sends 0x1000041 in its place):
// StateFieldLure::update sends it to the lure's target once the PC is back to idle
class MsgUnk_1000044 : public ::fw::Message {
public:
    MsgUnk_1000044() : fw::Message(0x1000044, 0x40) {}
};

}  // namespace gf

#endif
