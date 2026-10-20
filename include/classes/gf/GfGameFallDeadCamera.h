#ifndef CLASSES_GF_GFGAMEFALLDEADCAMERA_H
#define CLASSES_GF_GFGAMEFALLDEADCAMERA_H

#include "classes/fw/Camera.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B54798
class GfGameFallDeadCamera : public ::fw::Camera {
public:
    virtual ~GfGameFallDeadCamera();  // slot 0
    virtual void onActivate();  // slot 6
    virtual void update(fw::UpdateInfo const&);  // slot 8
};
}  // namespace gf

#endif
