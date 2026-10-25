#ifndef GF_MSGPCFIELDNOTIFYWATERWARP_H
#define GF_MSGPCFIELDNOTIFYWATERWARP_H

#include "fw/Message.h"

namespace gf {
class MsgPcFieldNotifyWarp;
// message 0x1000017 (1.0.0's MsgPcFieldNotifyWaterWarp, by the handlers that take it,
// AIAgentField::procMsgPcFieldNotifyWaterWarp and GfComBehaviorPc's; 1.0.0's StateFieldWaterPrepareWarp::update
// sends it with the same id): StateFieldWaterPrepareWarp::update tells the main characters where the PC warps to
class MsgPcFieldNotifyWaterWarp : public ::fw::Message {
public:
    MsgPcFieldNotifyWaterWarp(const MsgPcFieldNotifyWarp* warp) : fw::Message(0x1000017, 0x40), m_warp(warp) {}
    const MsgPcFieldNotifyWarp* m_warp;  // the PC's kept warp notice (the name is not the original's)
};
}  // namespace gf

#endif
