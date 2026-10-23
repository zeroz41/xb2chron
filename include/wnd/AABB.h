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

// whether two boxes touch within margin (BroadPhazeOctree::collectWindObj and detectAreaWind inline it; the name
// is not the original's)
inline bool isOverlap(const AABB& a, const AABB& b, float margin) {
    return a.min.x - b.max.x < margin && a.max.x - b.min.x > -margin && a.min.y - b.max.y < margin &&
           a.max.y - b.min.y > -margin && a.min.z - b.max.z < margin && a.max.z - b.min.z > -margin;
}
}  // namespace wnd

#endif
