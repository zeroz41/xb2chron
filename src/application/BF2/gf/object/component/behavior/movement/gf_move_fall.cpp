#include "classes/gf/GfMoveFallControler.h"
#include "fw/UpdateInfo.h"

namespace gf {

void GfMoveFallControler::update(const fw::UpdateInfo& info, Packet& packet) {
    const Param* param = packet.m_param.get<Param>();
    float speed = packet.m_speed - info.m_deltaTime * param->m_gravity;
    float limit = -param->m_maxSpeed;
    packet.m_speed = speed > limit ? speed : limit;
}

}  // namespace gf
