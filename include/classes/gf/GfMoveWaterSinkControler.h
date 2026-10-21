#ifndef CLASSES_GF_GFMOVEWATERSINKCONTROLER_H
#define CLASSES_GF_GFMOVEWATERSINKCONTROLER_H

#include "fw/ParamAdapter.h"

namespace fw { class UpdateInfo; }

namespace gf {
// no table: slows a vertical speed sinking into water; MoveUtilField::updateMoveWaterSink fills its packet
class GfMoveWaterSinkControler {
public:
    // its parameter block (the PC's param list's thirteenth entry)
    struct Param {
        float m_deceleration;  // taken off the speed's size per second
        float m_minSpeed;      // the size the speed keeps
    };
    struct Packet {
        float m_speed;  // vertical, upwards positive
        fw::ParamAdapter m_param;
    };
    void update(const fw::UpdateInfo& info, Packet& packet);
};
}  // namespace gf

#endif
