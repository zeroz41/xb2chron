#include "classes/gf/GfMoveTurnControler.h"
#include "fw/UpdateInfo.h"
#include "mm/Math.h"

namespace gf {

void GfMoveTurnControler::update(const fw::UpdateInfo& info, Packet& packet) {
    const Param* param = packet.m_param.get<Param>();
    const mm::Vec3& target = packet.m_target;
    const mm::Vec3& direction = packet.m_direction;
    float cos = direction.dot(target);
    // within [-1, 1], and as good as parallel taken as parallel
    if (cos < -1.0f) {
        cos = -1.0f;
    } else if (cos > 1.0f || cos > 0.9999f) {
        cos = 1.0f;
    }
    float angle = mm::acos(cos);
    float limit = param->m_minAngularSpeed + angle / 3.14159265f * (param->m_maxAngularSpeed - param->m_minAngularSpeed);
    mm::Vec3 axis = target.cross(direction);
    float speed = mm::fabs(angle / info.m_deltaTime);
    float sign = axis.dot(mm::Vec3::unitY) >= 0.0f ? -1.0f : 1.0f;
    packet.m_angularSpeed = (limit < speed ? limit : speed) * sign;
}

}  // namespace gf
