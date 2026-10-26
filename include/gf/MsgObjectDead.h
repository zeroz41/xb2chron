#ifndef GF_MSGOBJECTDEAD_H
#define GF_MSGOBJECTDEAD_H

#include "fw/Message.h"

namespace gf {

// message 0x1000039 (1.0.0's MsgObjectDead: 1.0.0's GfComProperty::procMsgObjectDead takes it as 0x1000036, zeroes
// the object's hit points and hands its type on as a MsgObjectNotifyDead's m_deadType; 1.0.0's
// GfGamePad::checkEmergencyEscape sends it as 0x1000036, 3.0.1's as 0x1000039): kills an object outright
class MsgObjectDead : public ::fw::Message {
public:
    explicit MsgObjectDead(int deadType) : fw::Message(0x1000039, 0x20), m_deadType(deadType) {}

    // the MsgObjectNotifyDead's m_deadType it causes (GfGamePad passes 4: killed outright; the name is not the
    // original's)
    int m_deadType;
};

}  // namespace gf

#endif
