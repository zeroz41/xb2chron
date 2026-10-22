#include "classes/gf/GfMoveJumpControler.h"
#include "fw/UpdateInfo.h"
#include "mm/Math.h"

namespace gf {

void GfMoveJumpControler::update(const fw::UpdateInfo& info, Packet& packet) {
    float deltaTime = info.m_deltaTime;
    const Param* param = packet.m_param.get<Param>();
    float target = param->m_maxSpeed * packet.m_inputRate;
    // the speed along the facing, and the facing, copied before the branches
    float speed = packet.m_velocity.dot(packet.m_direction);
    mm::Vec3 direction = packet.m_direction;
    if (target > speed) {
        speed = speed + deltaTime * param->m_acceleration;
        speed = speed < target ? speed : target;
    } else if (target < speed) {
        speed = speed - deltaTime * param->m_acceleration;
        speed = speed > target ? speed : target;
    }
    packet.m_velocity = direction * speed;
    calcAngularVelocity(info.m_deltaTime, packet);
}

void GfMoveJumpControler::calcAngularVelocity(float deltaTime, Packet& packet) {
    const Param* param = packet.m_param.get<Param>();
    const mm::Vec3& target = packet.m_inputDirection;
    const mm::Vec3& direction = packet.m_direction;
    float cos = direction.dot(target);
    // within [-1, 1], and as good as parallel taken as parallel
    if (cos < -1.0f) {
        cos = -1.0f;
    } else if (cos > 1.0f || cos > 0.99f) {
        cos = 1.0f;
    }
    float angle = mm::acos(cos);
    mm::Vec3 axis = target.cross(direction);
    float speed = angle / deltaTime;
    float size = mm::fabs(speed);
    float sign = axis.dot(mm::Vec3::unitY) >= 0.0f ? -1.0f : 1.0f;
    float velocity = size * sign;
    if (velocity > packet.m_angularVelocity) {
        packet.m_angularVelocity = packet.m_angularVelocity + param->m_angularAcceleration * deltaTime;
    } else if (packet.m_angularVelocity > velocity) {
        packet.m_angularVelocity = packet.m_angularVelocity - param->m_angularAcceleration * deltaTime;
    }
    packet.m_angularVelocity = mm::clamp(packet.m_angularVelocity, -speed, speed);
    packet.m_angularVelocity =
        mm::clamp(packet.m_angularVelocity, -param->m_maxAngularVelocity, param->m_maxAngularVelocity);
}

}  // namespace gf
