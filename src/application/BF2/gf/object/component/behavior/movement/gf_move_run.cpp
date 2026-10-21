#include "classes/gf/GfMoveRunControler.h"
#include "mm/Math.h"

namespace gf {

// enter (0x71004A8630) and update (0x71004A868C) are not matched yet

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

}  // namespace gf
