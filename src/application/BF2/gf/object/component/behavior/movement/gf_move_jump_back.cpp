#include "classes/gf/GfMoveJumpBackControler.h"
#include "fw/UpdateInfo.h"

namespace gf {

void GfMoveJumpBackControler::update(const fw::UpdateInfo& info, Packet& packet) {
    const Param* param = packet.m_param.get<Param>();
    const mm::Vec3& direction = packet.m_direction;
    float limit = -(param->m_minSpeedRate * packet.m_inputLength);
    float speed = packet.m_velocity.dot(direction) - param->m_deceleration * info.m_deltaTime;
    speed = speed > limit ? speed : limit;
    packet.m_velocity = direction * speed;
}

}  // namespace gf
