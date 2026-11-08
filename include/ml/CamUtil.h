#ifndef ML_CAMUTIL_H
#define ML_CAMUTIL_H

#include "mm/Mat44.h"
#include "mm/Vec3.h"

namespace ml {
// a camera's coordinate helpers: a view-space position and its device coordinates through a projection matrix
// (the parameter names are not the original's)
class CamUtil {
public:
    static void getViewLocalToDeviceCoord(mm::Vec3& out, const mm::Mat44& proj, const mm::Vec3& pos);
    static void getDeviceCoordToViewLocal(mm::Vec3& out, const mm::Mat44& proj, const mm::Vec3& pos);
};
}  // namespace ml

#endif
