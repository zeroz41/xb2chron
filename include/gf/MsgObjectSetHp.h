#ifndef GF_MSGOBJECTSETHP_H
#define GF_MSGOBJECTSETHP_H

#include "fw/Message.h"

namespace gf {
// message 0x1000038 (1.0.0's MsgObjectSetHp, by GfComProperty::procMsgObjectSetHp that takes it and stores the word at
// 0x8 as the hit points; 3.0.1's recieveMessage does the same inline): sets an object's hit points
class MsgObjectSetHp : public ::fw::Message {
public:
    explicit MsgObjectSetHp(unsigned int hp) : fw::Message(0x1000038, 0x20), m_hp(hp) {}
    unsigned int m_hp;  // the name is not the original's
};
}  // namespace gf

#endif
