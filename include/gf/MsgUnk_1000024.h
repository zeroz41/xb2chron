#ifndef GF_MSGUNK_1000024_H
#define GF_MSGUNK_1000024_H

#include "fw/Message.h"

namespace gf {

// message 0x1000024 (no name for it survives): GfGamePlayerUniqueScheduler::judge asks a waiting party member with it
// whether it can play a unique motion now; the receiver sets m_result
class MsgUnk_1000024 : public ::fw::Message {
public:
    MsgUnk_1000024() : fw::Message(0x1000024, 0x40), m_result(false) {}

    bool m_result;  // the name is not the original's
};

}  // namespace gf

#endif
