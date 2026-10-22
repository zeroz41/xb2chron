#ifndef WND_TRANSFORM_H
#define WND_TRANSFORM_H

#include "mm/Quat.h"
#include "mm/Vec3.h"

namespace wnd {
// where a wind object is and how it is turned: WindObject's constructor copies its create-info's, and
// SphereShape::calcAABB centres the box on position
class Transform {
public:
    mm::Vec3 position;
    mm::Quat rotation;
};
}  // namespace wnd

#endif
