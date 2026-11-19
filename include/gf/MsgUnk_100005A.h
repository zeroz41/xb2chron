#ifndef GF_MSGUNK_100005A_H
#define GF_MSGUNK_100005A_H

#include "fw/Message.h"

namespace gf {

// message 0x100005A (no name for it survives): GfGameScene::setIraBoneMount sends it, with its flag after the
// header, to the target's appended objects (the field name is not the original's)
class MsgUnk_100005A : public ::fw::Message {
public:
    explicit MsgUnk_100005A(bool flag) : fw::Message(0x100005A, 0x80), m_flag(flag) {}

    bool m_flag;  // setIraBoneMount's flag
};

}  // namespace gf

#endif
