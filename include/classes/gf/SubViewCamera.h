#ifndef CLASSES_GF_SUBVIEWCAMERA_H
#define CLASSES_GF_SUBVIEWCAMERA_H

#include "classes/fw/Camera.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B45E08
class SubViewCamera : public ::fw::Camera {
public:
    virtual ~SubViewCamera();  // slot 0
    virtual void getRTTI() const;  // slot 2
    virtual void getName() const;  // slot 3
    virtual void onActivate();  // slot 6
    virtual void update(fw::UpdateInfo const&);  // slot 8
};
}  // namespace gf

#endif
