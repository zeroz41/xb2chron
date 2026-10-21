#ifndef CLASSES_GF_GFMOVERUNCONTROLER_H
#define CLASSES_GF_GFMOVERUNCONTROLER_H

#include "fw/ParamAdapter.h"
#include "mm/Vec3.h"

namespace fw { class UpdateInfo; }

namespace gf {
// no table: running (and swimming) along the facing, turning it towards the stick; gf::pc::setMoveRunPacket and
// setMoveSwimPacket fill its packet from the PC's property
class GfMoveRunControler {
public:
    // its parameter block (the PC's param list's fourth entry when running)
    struct Param {
        float m_minSpeed;         // the speed without stick input
        float m_maxSpeed;         // at full stick, times the packet's speed rate
        float m_acceleration;     // the speed's rise per second
        float m_deceleration;     // the speed's fall per second
        float m_minAngularSpeed;  // the turning speed's limit when the stick points ahead
        float m_maxAngularSpeed;  // the limit when it points behind
    };
    struct Packet {
        mm::Vec3 m_velocity;
        float m_angularVelocity;  // radians per second about the up axis
        fw::ParamAdapter m_param;
        float m_inputRate;          // the stick's tilt past its dead zone, within [0, 1]
        mm::Vec3 m_inputDirection;  // the stick's direction in the camera's frame (the facing without input)
        mm::Vec3 m_direction;       // the direction faced
        float m_speedRate;          // scales the full-stick speed (bonuses)
        float m_speedBonus;         // added to the full-stick speed
    };
    void enter(Packet& packet, bool accelerate);
    void update(const fw::UpdateInfo& info, Packet& packet);
    void calcAngularVelocity(float deltaTime, Packet& packet);
};
}  // namespace gf

#endif
