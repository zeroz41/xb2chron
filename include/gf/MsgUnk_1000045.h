#ifndef GF_MSGUNK_1000045_H
#define GF_MSGUNK_1000045_H

#include "fw/Message.h"

namespace gf {
// message 0x1000045 (no name for it survives): GfComProperty::recieveMessage sets the object's sound variable 1
// (getSoundVariableName) to its word at 0x8 (the field name is not the original's)
class MsgUnk_1000045 : public ::fw::Message {
public:
    explicit MsgUnk_1000045(int value) : fw::Message(0x1000045, 0x20), m_value(value) {}
    int m_value;
    // GfGameUtil::setBladeSelect sends the attribute after the change in m_value and the one before here (the name is
    // not the original's)
    int pad_C;
};
}  // namespace gf

#endif
