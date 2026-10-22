#ifndef CLASSES_GF_GFGAMEFALLDEADCAMERA_H
#define CLASSES_GF_GFGAMEFALLDEADCAMERA_H

#include "classes/fw/Camera.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B54798; GfDeadCamera makes one for a fall (its constructor is inline there)
class GfGameFallDeadCamera : public ::fw::Camera {
public:
    GfGameFallDeadCamera() : fw::Camera(fw::CAMERA_PRIO(55)) {
        m_offset = mm::Vec3::zero;
    }
    virtual ~GfGameFallDeadCamera();  // slot 0
    virtual void onActivate();  // slot 6
    virtual void update(fw::UpdateInfo const&);  // slot 8

    mm::Vec3 m_offset;  // the camera target minus the player's position, on activation
    mm::Vec3 m_eye;  // GfInfo::m_camPos, on activation
    mm::Vec3 m_target;  // the player's position plus m_offset
};
}  // namespace gf

#endif
