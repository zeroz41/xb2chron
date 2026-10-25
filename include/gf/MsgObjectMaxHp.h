#ifndef GF_MSGOBJECTMAXHP_H
#define GF_MSGOBJECTMAXHP_H

#include "fw/Message.h"

namespace gf {

// message 0x1000037 (1.0.0's MsgObjectMaxHp, by GfComProperty::procMsgObjectMaxHp that takes it and stores the word
// at 0x8 as the maximum hit points): sets an object's maximum hit points
class MsgObjectMaxHp : public ::fw::Message {
public:
    explicit MsgObjectMaxHp(unsigned int hpMax) : fw::Message(0x1000037, 0x20), m_hpMax(hpMax) {}

    unsigned int m_hpMax;  // the name is not the original's
};

}  // namespace gf

#endif
