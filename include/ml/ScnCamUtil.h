#ifndef ML_SCNCAMUTIL_H
#define ML_SCNCAMUTIL_H

#include "mm/Vec3.h"

namespace ml { class ScnObjCam; }

namespace ml {
// a camera's screen helpers
class ScnCamUtil {
public:
    // where pos shows on the camera's screen, from the render thread's information unless cpu; false when it does
    // not show
    static bool getScreenPos(mm::Vec3& out, const ScnObjCam* cam, const mm::Vec3& pos);
    static bool getScreenPos(mm::Vec3& out, const ScnObjCam* cam, bool cpu, const mm::Vec3& pos);
};
}  // namespace ml

#endif
