#ifndef GF_MSGPCFIELDWATERWARPBUDDY_H
#define GF_MSGPCFIELDWATERWARPBUDDY_H

#include "fw/Message.h"

namespace gf {

// message 0x1000021 (1.0.0's MsgPcFieldWaterWarpBuddy, by the handler that takes it; 1.0.0's id is 0x1000020): asks a
// PC to act on AIAgentField's buddy water warp notice (MsgPcFieldNotifyWaterWarpBuddy, 0x100001F);
// StateFieldWaterNormal::procMsgPcFieldWaterWarpBuddy accepts it
class MsgPcFieldWaterWarpBuddy : public ::fw::Message {
public:
    MsgPcFieldWaterWarpBuddy() : fw::Message(0x1000021, 0x40), m_accepted(false) {}

    bool m_accepted;  // the handler's answer (the name is not the original's)
};

}  // namespace gf

#endif
