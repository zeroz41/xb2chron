#ifndef CLASSES_GF_GFMOVEJUMPBACKCONTROLER_H
#define CLASSES_GF_GFMOVEJUMPBACKCONTROLER_H

#include "fw/ParamAdapter.h"
#include "mm/Vec3.h"

namespace fw { class UpdateInfo; }

namespace gf {
// no table: the speed along a back jump's direction; MoveUtilField::updateMoveJumpBack fills its packet
class GfMoveJumpBackControler {
public:
    // its parameter block (the PC's param list's eighth entry)
    struct Param {
        float m_minSpeedRate;  // times the packet's input length: how far below zero the speed may go
        float m_deceleration;  // taken off the speed per second
    };
    struct Packet {
        mm::Vec3 m_velocity;
        fw::ParamAdapter m_param;
        float m_inputLength;  // the length of the stick's input in the camera's frame, 0 or more
        mm::Vec3 m_direction;
    };
    void update(const fw::UpdateInfo& info, Packet& packet);
};
}  // namespace gf

#endif
