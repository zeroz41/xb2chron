#ifndef CLASSES_GF_GFMOVEFALLCONTROLER_H
#define CLASSES_GF_GFMOVEFALLCONTROLER_H

#include "fw/ParamAdapter.h"

namespace fw { class UpdateInfo; }

namespace gf {
// no table: the fall's vertical speed; MoveUtilField::updateFallDown fills its packet from the PC's property
class GfMoveFallControler {
public:
    // its parameter block (the PC's param list's ninth entry)
    struct Param {
        float m_gravity;   // taken off the speed per second
        float m_maxSpeed;  // the speed's limit downwards
    };
    struct Packet {
        float m_speed;  // vertical, upwards positive
        fw::ParamAdapter m_param;
    };
    void update(const fw::UpdateInfo& info, Packet& packet);
};
}  // namespace gf

#endif
