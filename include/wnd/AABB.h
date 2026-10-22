#ifndef WND_AABB_H
#define WND_AABB_H

#include "mm/Vec3.h"

namespace wnd {
// an axis-aligned box: SphereShape::calcAABB writes the position less the radius to min and plus it to max
class AABB {
public:
    mm::Vec3 min;
    mm::Vec3 max;
};
}  // namespace wnd

#endif
