#ifndef GF_MSGPCFIELDNOTIFYWATERWARPBUDDY_H
#define GF_MSGPCFIELDNOTIFYWATERWARPBUDDY_H

#include "fw/Message.h"

namespace gf {
class MsgPcFieldNotifyWarp;

// message 0x1000020 (1.0.0's MsgPcFieldNotifyWaterWarpBuddy, by the handlers that take it,
// AIAgentField::procMsgPcFieldNotifyWaterWarpBuddy and GfComBehaviorPc's; 1.0.0's StateFieldWaterWarpDive::update
// sends it with 1.0.0's id 0x100001F): StateFieldWaterWarpDive::update tells the buddies where the PC warps to
class MsgPcFieldNotifyWaterWarpBuddy : public ::fw::Message {
public:
    MsgPcFieldNotifyWaterWarpBuddy(const MsgPcFieldNotifyWarp* warp) : fw::Message(0x1000020, 0x40), m_warp(warp) {}

    const MsgPcFieldNotifyWarp* m_warp;  // the PC's kept warp notice (the name is not the original's)
};

}  // namespace gf

#endif
