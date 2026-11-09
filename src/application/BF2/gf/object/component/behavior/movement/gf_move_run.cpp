#include "classes/gf/GfMoveRunControler.h"
#include "mm/Math.h"
#include "mm/Quat.h"
#include "fw/UpdateInfo.h"

namespace gf {

void GfMoveRunControler::enter(Packet& packet, bool accelerate) {
    const Param* param = packet.m_param.get<Param>();
    const mm::Vec3& direction = packet.m_direction;
    if (accelerate) {
        float speed = param->m_minSpeed + (param->m_maxSpeed * packet.m_speedRate - param->m_minSpeed) * packet.m_inputRate;
        packet.m_velocity = mm::Vec3(speed * direction.x, speed * direction.y, speed * direction.z);
    } else {
        packet.m_velocity = direction * param->m_minSpeed;
    }
}

void GfMoveRunControler::update(const fw::UpdateInfo& info, Packet& packet) {
    calcAngularVelocity(info.m_deltaTime, packet);
    float angle = packet.m_angularVelocity * info.m_deltaTime;
    float half = angle * 0.5f;
    mm::Quat rotation(0.0f, ::sinf(half), 0.0f, ::cosf(half));
    rotation.rotate(packet.m_direction, packet.m_direction);
    calcVelocity(info.m_deltaTime, packet);
}

void GfMoveRunControler::calcAngularVelocity(float deltaTime, Packet& packet) {
    const Param* param = packet.m_param.get<Param>();
    const mm::Vec3& target = packet.m_inputDirection;
    const mm::Vec3& direction = packet.m_direction;
    float cos = mm::clamp(direction.dot(target), -1.0f, 1.0f);
    float angle = mm::acos(cos);
    float limit = param->m_minAngularSpeed + angle / 3.14159265f * (param->m_maxAngularSpeed - param->m_minAngularSpeed);
    float speed = mm::fabs(angle / deltaTime);
    mm::Vec3 axis = target.cross(direction);
    float sign = axis.dot(mm::Vec3::unitY) >= 0.0f ? -1.0f : 1.0f;
    packet.m_angularVelocity = (limit < speed ? limit : speed) * sign;
}

inline void GfMoveRunControler::calcVelocity(float deltaTime, Packet& packet) {
    const Param* param = packet.m_param.get<Param>();
    float maxSpeed = param->m_maxSpeed * packet.m_speedRate + packet.m_speedBonus;
    float target = (maxSpeed - param->m_minSpeed) * packet.m_inputRate + param->m_minSpeed;
    float speed = packet.m_velocity.length();
    if (target > speed) {
        speed += deltaTime * param->m_acceleration;
        speed = speed < target ? speed : target;
    } else if (target < speed) {
        speed -= deltaTime * param->m_deceleration;
        speed = speed > target ? speed : target;
    }
    packet.m_velocity = mm::Vec3(speed * packet.m_direction.x, speed * packet.m_direction.y, speed * packet.m_direction.z);
}

}  // namespace gf
