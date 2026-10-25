#ifndef GF_MSGUNK_1000048_H
#define GF_MSGUNK_1000048_H

#include "fw/Message.h"

namespace gf {

// message 0x1000048 (no name for it survives): GfObjUtil::setLimitHP sends it to the object with the hit points (the field names are not the original's)
class MsgUnk_1000048 : public ::fw::Message {
public:
    explicit MsgUnk_1000048(unsigned int hp) : fw::Message(0x1000048, 0x20), m_hp(hp) {}

    unsigned int m_hp;
};

}  // namespace gf

#endif
