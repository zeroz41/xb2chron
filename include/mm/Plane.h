#ifndef MM_PLANE_H
#define MM_PLANE_H

#include "mm/Vec3.h"

namespace mm {

// a plane: its normal and its distance (mm::Cube::getPlanes fills a FixedArray<mm::Plane, 6>; a camera keeps six,
// 0x20 apart, ScnObjCam::getPlaneGbl). The field and constructor names are not the original's.
class Plane {
public:
    Plane() {}
    // through pos, facing normal (made length 1; one too short becomes zero), GfInfo::initialize's planes
    Plane(const Vec3& normal, const Vec3& pos) {
        Vec3 n = normal;
        float length = n.length();
        if (length <= 1e-6f) {
            this->normal = Vec3::zero;
        } else {
            this->normal = n * (1.0f / length);
        }
        d = -this->normal.dot(pos);
    }

    Vec3 normal;
    float d;
};

}  // namespace mm

#endif
