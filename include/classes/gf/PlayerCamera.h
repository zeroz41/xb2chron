#ifndef CLASSES_GF_PLAYERCAMERA_H
#define CLASSES_GF_PLAYERCAMERA_H

#include "classes/fw/Camera.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B45AE8
class PlayerCamera : public ::fw::Camera {
public:
    virtual ~PlayerCamera();  // slot 0
    virtual void getRTTI() const;  // slot 2
    virtual void getName() const;  // slot 3
    virtual void onActivate();  // slot 6
    virtual void update(fw::UpdateInfo const&);  // slot 8
    virtual void updateViewMatrix();  // slot 9
};
}  // namespace gf

#endif
