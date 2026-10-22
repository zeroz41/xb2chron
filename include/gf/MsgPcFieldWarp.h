#ifndef GF_MSGPCFIELDWARP_H
#define GF_MSGPCFIELDWARP_H

#include "fw/Message.h"
#include "fw/Transform.h"

namespace gf {

// message 0x1000019 (1.0.0's MsgPcFieldWarp: GfComBehaviorPc::recieveMessage takes it, procMsgPcFieldWarp's case): puts
// a PC at a transform, at once (GfComBehaviorPc::warpExternal) when m_immediate is set, through its property's
// pending warp otherwise
class MsgPcFieldWarp : public ::fw::Message {
public:
    MsgPcFieldWarp() : fw::Message(0x1000019, 0x40), m_immediate(true), m_accepted(false) {}

    unsigned char pad_8[0x8];
    fw::Transform m_transform;
    bool m_immediate;  // (the name is not the original's)
    bool m_accepted;   // the handler's answer (the name is not the original's)
};

}  // namespace gf

#endif
