#ifndef GF_MSGPCFIELDWATERWARP_H
#define GF_MSGPCFIELDWATERWARP_H

#include "fw/Message.h"

namespace gf {

// message 0x1000018 (1.0.0's MsgPcFieldWaterWarp, by the handler that takes it): asks a PC to act on AIAgentField's
// water warp notice (MsgPcFieldNotifyWaterWarp, 0x1000017); StateFieldWaterNormal::procMsgPcFieldWaterWarp accepts it
// when its asm command runs
class MsgPcFieldWaterWarp : public ::fw::Message {
public:
    MsgPcFieldWaterWarp() : fw::Message(0x1000018, 0x40), m_accepted(false) {}

    bool m_accepted;  // the handler's answer (the name is not the original's)
};

}  // namespace gf

#endif
