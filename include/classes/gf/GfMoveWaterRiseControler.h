#ifndef CLASSES_GF_GFMOVEWATERRISECONTROLER_H
#define CLASSES_GF_GFMOVEWATERRISECONTROLER_H

#include "fw/ParamAdapter.h"

namespace fw { class UpdateInfo; }

namespace gf {
// no table: the vertical speed rising through water; MoveUtilField::updateMoveWaterRise and
// updateMoveWaterHoleRise fill its packet from the PC's property
class GfMoveWaterRiseControler {
public:
    // its parameter block (the PC's param list's fourteenth entry)
    struct Param {
        float m_acceleration;  // added to the speed per second while rising
        float m_maxSpeed;      // the rising speed's limit
        float m_deceleration;  // taken off the speed's size per second while slowing
        float m_minSpeed;      // the size the slowing speed keeps
    };
    struct Packet {
        float m_speed;  // vertical, upwards positive
        fw::ParamAdapter m_param;
        bool m_decelerate;  // slow down instead of rising (set near the surface)
    };
    void update(const fw::UpdateInfo& info, Packet& packet);
};
}  // namespace gf

#endif
