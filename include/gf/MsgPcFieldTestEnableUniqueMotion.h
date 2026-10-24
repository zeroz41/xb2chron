#ifndef GF_MSGPCFIELDTESTENABLEUNIQUEMOTION_H
#define GF_MSGPCFIELDTESTENABLEUNIQUEMOTION_H

#include "fw/Message.h"

namespace gf {

// message 0x1000024 (1.0.0's MsgPcFieldTestEnableUniqueMotion, by
// StateFieldIdle::procMsgPcFieldTestEnableUniqueMotion's parameter): GfGamePlayerUniqueScheduler::judge asks a
// waiting party member with it whether it can play a unique motion now; the receiver sets m_result
class MsgPcFieldTestEnableUniqueMotion : public ::fw::Message {
public:
    MsgPcFieldTestEnableUniqueMotion() : fw::Message(0x1000024, 0x40), m_result(false) {}

    bool m_result;  // the name is not the original's
};

}  // namespace gf

#endif
