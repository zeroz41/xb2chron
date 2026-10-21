#ifndef CLASSES_GF_GFMOVETURNCONTROLER_H
#define CLASSES_GF_GFMOVETURNCONTROLER_H

#include "fw/ParamAdapter.h"
#include "mm/Vec3.h"

namespace fw { class UpdateInfo; }

namespace gf {
// no table: the turning speed about the up axis from the facing towards a target direction;
// MoveUtilField::updateMoveTurn, updateMoveWalkTurn and updateMoveWaterTurn fill its packet
class GfMoveTurnControler {
public:
    // its parameter block (the PC's param list's fifth entry for updateMoveTurn)
    struct Param {
        float m_minAngularSpeed;  // the turning speed's limit when the target is straight ahead
        float m_maxAngularSpeed;  // the limit when it is straight behind
    };
    struct Packet {
        float m_angularSpeed;  // radians per second, the sign giving the side
        fw::ParamAdapter m_param;
        mm::Vec3 m_target;     // the direction to turn to
        mm::Vec3 m_direction;  // the direction faced
    };
    void update(const fw::UpdateInfo& info, Packet& packet);
};
}  // namespace gf

#endif
