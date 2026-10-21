#include "classes/gf/GfMoveWaterRiseControler.h"
#include "fw/UpdateInfo.h"

namespace gf {

void GfMoveWaterRiseControler::update(const fw::UpdateInfo& info, Packet& packet) {
    const Param* param = packet.m_param.get<Param>();
    float speed = packet.m_speed;
    if (packet.m_decelerate) {
        float sign = speed >= 0.0f ? 1.0f : -1.0f;
        float size = speed * sign - info.m_deltaTime * param->m_deceleration;
        packet.m_speed = sign * (size > param->m_minSpeed ? size : param->m_minSpeed);
    } else {
        speed = speed + info.m_deltaTime * param->m_acceleration;
        packet.m_speed = speed < param->m_maxSpeed ? speed : param->m_maxSpeed;
    }
}

}  // namespace gf
