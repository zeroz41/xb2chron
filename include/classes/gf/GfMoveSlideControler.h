#ifndef CLASSES_GF_GFMOVESLIDECONTROLER_H
#define CLASSES_GF_GFMOVESLIDECONTROLER_H

#include "fw/ParamAdapter.h"
#include "mm/Vec3.h"

namespace fw { class Reflection; }
namespace fw { class UpdateInfo; }

namespace gf {
// no table: steering across a slope while sliding down it, turning to face down the slope;
// gf::pc::setMoveSlidePacket fills its packet from the PC's property and a gf::pc::SlideParam
class GfMoveSlideControler {
public:
    // its parameter block (the PC's param list's eighteenth entry)
    struct Param {
        float m_sideSpeed;        // across the slope at full stick (sideSpeed)
        float m_brake;            // how fast stick input up the slope slows the slide (frontBrake)
        float m_minAngularSpeed;  // the turning speed's limit when facing down the slope (angularVelMin)
        float m_maxAngularSpeed;  // the limit when facing up it (angularVelMax)
    };
    struct Packet {
        mm::Vec3 m_velocity;      // across the slope
        float m_angularVelocity;  // radians per second about the up axis
        float m_slideSpeed;       // down the slope
        fw::ParamAdapter m_param;
        float m_inputRate;          // the stick's tilt past its dead zone, within [0, 1]
        mm::Vec3 m_inputDirection;  // the stick's direction in the camera's frame, zero without input
        mm::Vec3 m_direction;       // the direction faced
        mm::Vec3 m_normal;          // the ground's
        float m_minSlideSpeed;      // the slide speed braking keeps (the SlideParam's)
    };
    // its Param's values as a struct of the reflection at index (1.0.0's; 3.0.1's linker dropped it)
    static void createReflection(fw::Reflection* reflection, const char* name, unsigned int index);
    void update(const fw::UpdateInfo& info, Packet& packet);
};
}  // namespace gf

#endif
