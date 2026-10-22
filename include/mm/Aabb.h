#ifndef MM_AABB_H
#define MM_AABB_H

#include "mm/Vec3.h"

namespace mm {

// an axis-aligned bounding box: its least and greatest corners (Vec3s, 16 bytes apart)
class Aabb {
public:
    void set(const Vec3& a, const Vec3& b);

    Vec3 m_min;
    Vec3 m_max;
};

}  // namespace mm

#endif
