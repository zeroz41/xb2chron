#ifndef CLASSES_GF_GFMOVEJUMPCONTROLER_H
#define CLASSES_GF_GFMOVEJUMPCONTROLER_H

#include "fw/ParamAdapter.h"
#include "mm/Vec3.h"

namespace fw { class UpdateInfo; }

namespace gf {
// no table: a jump's speed along its facing and its turning towards the stick; gf::pc::setMoveJumpPacket fills
// its packet from the PC's property
class GfMoveJumpControler {
public:
    // its parameter block (the PC's param list's seventh entry)
    struct Param {
        float m_maxSpeed;             // at full stick
        float m_acceleration;         // the speed's change per second towards it
        float m_maxAngularVelocity;   // the turning speed's limit
        float m_angularAcceleration;  // the turning speed's change per second
    };
    struct Packet {
        mm::Vec3 m_velocity;
        float m_angularVelocity;  // radians per second about the up axis
        fw::ParamAdapter m_param;
        float m_inputRate;          // the stick's tilt in the camera's frame, within [0, 1]
        mm::Vec3 m_inputDirection;  // the stick's direction in the camera's frame (the facing without input)
        mm::Vec3 m_direction;       // the direction faced
    };
    void update(const fw::UpdateInfo& info, Packet& packet);
    void calcAngularVelocity(float deltaTime, Packet& packet);
};
}  // namespace gf

#endif
