#include "classes/gf/GfMoveBrakeControler.h"
#include "fw/UpdateInfo.h"

namespace gf {

void GfMoveBrakeControler::update(const fw::UpdateInfo& info, Packet& packet) {
    const Param* param = packet.m_param.get<Param>();
    mm::Vec3& velocity = packet.m_velocity;
    float speed = velocity.length() - param->m_deceleration * info.m_deltaTime;
    speed = speed > 0.0f ? speed : 0.0f;
    velocity.normalize();
    velocity.x = speed * velocity.x;
    velocity.y = speed * velocity.y;
    velocity.z = speed * velocity.z;
}

}  // namespace gf
