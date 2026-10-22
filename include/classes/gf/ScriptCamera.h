#ifndef CLASSES_GF_SCRIPTCAMERA_H
#define CLASSES_GF_SCRIPTCAMERA_H

#include "mm/mtl/IntrusivePtr.h"
#include "classes/fw/Camera.h"

namespace mm { class Vec3; }

namespace gf {
// table 0x7100B45F70: a script's camera: start pushes a gf::ScriptCameraEntity onto the camera manager's first
// layer, move moves it, end pops it (times in frames at 30 a second)
class ScriptCamera {
public:
    ScriptCamera();
    virtual ~ScriptCamera();  // slot 0
    void start(const mm::Vec3& pos, const mm::Vec3& rot, float frames);
    void end(float frames);
    void move(const mm::Vec3& pos, const mm::Vec3& rot, float frames);

    mm::mtl::IntrusivePtr<fw::Camera> m_camera;  // the entity while started
};
}  // namespace gf

#endif
