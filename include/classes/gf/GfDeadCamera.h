#ifndef CLASSES_GF_GFDEADCAMERA_H
#define CLASSES_GF_GFDEADCAMERA_H

#include "mm/mtl/IntrusivePtr.h"

namespace fw { class Camera; }

namespace gf {
// how the player died: GfDeadCamera makes a camera for 4 (a fall); the names are unknown
enum GfPlayerDead : int {};

// no table: holds the camera it pushed onto the camera manager's first layer
class GfDeadCamera {
public:
    GfDeadCamera(GfPlayerDead dead);
    ~GfDeadCamera();

    mm::mtl::IntrusivePtr<fw::Camera> m_camera;
};
}  // namespace gf

#endif
