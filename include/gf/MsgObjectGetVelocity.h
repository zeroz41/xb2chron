#ifndef GF_MSGOBJECTGETVELOCITY_H
#define GF_MSGOBJECTGETVELOCITY_H

#include "fw/Message.h"
#include "mm/Vec3.h"

namespace gf {

// message 0x1000049: asks an object how fast it moves; GfComPropertyEvent answers along its facing
class MsgObjectGetVelocity : public ::fw::Message {
public:
    // the question: no velocity yet (FootStepPlugin::update's)
    MsgObjectGetVelocity() : fw::Message(0x1000049, 0x40), m_velocity(mm::Vec3::zero) {}
    mm::Vec3 m_velocity;  // the answer
};

}  // namespace gf

#endif
