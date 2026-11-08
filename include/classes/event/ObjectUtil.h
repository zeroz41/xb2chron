#ifndef CLASSES_EVENT_OBJECTUTIL_H
#define CLASSES_EVENT_OBJECTUTIL_H

namespace mm { class Vec3; }
namespace gf { class GF_OBJ_HANDLE; }

namespace event {
// helpers of the event objects (no table)
class ObjectUtil {
public:
    // prints "CAM0", "pos:", "tar:", "rot:" (in degrees) and "fov:"/"foc:" at (x, y); ObjectCamera::OnBouRender calls it
    static void drawCameraInfo(int x, int y, mm::Vec3 const& pos, mm::Vec3 const& tar, mm::Vec3 const& rot, float fov,
                               bool);
    // the object's animation state name (its GfComEvtAnim's, else its GfComAsm's layer 0) in a box above pos
    // (height + 0.2 up); ObjectChara::render calls it
    static void drawState(mm::Vec3 const& pos, float height, gf::GF_OBJ_HANDLE* handle);
};
}  // namespace event

#endif
