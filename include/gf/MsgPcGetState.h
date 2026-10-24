#ifndef GF_MSGPCGETSTATE_H
#define GF_MSGPCGETSTATE_H

#include "fw/Message.h"

namespace gf {

// message 0x1000005 (1.0.0's MsgPcGetState: GfComBehaviorPc::procMsgPcGetState stores the current state's ID at
// its 0x8): asks a PC which state it is in (StateFieldWaterNormal::procMsgPcFieldWaterWarp builds one on the stack)
class MsgPcGetState : public ::fw::Message {
public:
    MsgPcGetState() : fw::Message(0x1000005, 0x40), m_state(-1) {}
    int m_state;  // the state's ID, -1 for none (the name is not the original's)
};

}  // namespace gf

#endif
