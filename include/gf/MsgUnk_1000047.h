#ifndef GF_MSGUNK_1000047_H
#define GF_MSGUNK_1000047_H

#include "fw/Message.h"

namespace gf {

// message 0x1000047 (no name for it survives): GfObjUtil::setInvincible sends it to the object with its two flags (the field names are not the original's)
class MsgUnk_1000047 : public ::fw::Message {
public:
    MsgUnk_1000047(bool on, bool value2) : fw::Message(0x1000047, 0x20), m_on(on), m_value2(value2) {}

    bool m_on;
    bool m_value2;  // setInvincible's second flag (its meaning is not known)
};

}  // namespace gf

#endif
