#include "mm/Vec3.h"
#include "mm/Quat.h"
#include "mm/mtl/IntrusivePtr.h"
#include "classes/gf/GfComponent.h"
#include "classes/gf/GfComProperty.h"
#include "classes/gf/GfComTransform.h"
#include "classes/gf/GfComPropertyEvent.h"
#include "gf/MsgObjectGetVelocity.h"
#include "classes/fw/UpdatableObject.h"

namespace gf {

GfComPropertyEvent::GfComPropertyEvent() : m_moveSpeed(0.0f) {}

void GfComPropertyEvent::setup(const SetupInfo& info) {}

void GfComPropertyEvent::cleanup() {}

void GfComPropertyEvent::setMoveSpeed(float speed) {
    m_moveSpeed = speed;
}

bool GfComPropertyEvent::recieveMessage(fw::MessageObject* sender, fw::Message& msg) {
    if (msg.m_id == 0x1000049) {
        procMsgObjectGetVelocity(sender, static_cast<MsgObjectGetVelocity&>(msg));
        return true;
    }
    return GfComProperty::recieveMessage(sender, msg);
}

void GfComPropertyEvent::procMsgObjectGetVelocity(fw::MessageObject* sender, MsgObjectGetVelocity& msg) {
    GfComTransform* transform = m_owner->getComponent<GfComTransform>(0);
    if (transform != nullptr) {
        msg.m_velocity = transform->getRotation().rotate(mm::Vec3::unitZ) * m_moveSpeed;
    }
}

mm::mtl::RTTI GfComPropertyEvent::m_rtti("GfComPropertyEvent", &GfComProperty::m_rtti, nullptr);

}  // namespace gf
