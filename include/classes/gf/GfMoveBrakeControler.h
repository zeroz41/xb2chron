#ifndef CLASSES_GF_GFMOVEBRAKECONTROLER_H
#define CLASSES_GF_GFMOVEBRAKECONTROLER_H

#include "fw/ParamAdapter.h"
#include "mm/Vec3.h"

namespace fw { class UpdateInfo; }

namespace gf {
// no table: slows a velocity down along its own direction; MoveUtilField::updateBrake fills its packet
class GfMoveBrakeControler {
public:
    // its parameter block (the PC's param list's second entry)
    struct Param {
        float m_deceleration;  // taken off the speed per second
    };
    struct Packet {
        mm::Vec3 m_velocity;
        fw::ParamAdapter m_param;
    };
    void update(const fw::UpdateInfo& info, Packet& packet);
};
}  // namespace gf

#endif
