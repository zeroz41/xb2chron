#ifndef MM_PLANE_H
#define MM_PLANE_H

#include "mm/Vec3.h"

namespace mm {

// a plane: its normal and its distance (mm::Cube::getPlanes fills a FixedArray<mm::Plane, 6>; a camera keeps six,
// 0x20 apart, ScnObjCam::getPlaneGbl). The field and constructor names are not the original's.
class Plane {
public:
    Plane() {}
    // through pos, facing normal (made length 1; one too short becomes zero), GfInfo::initialize's planes. The
    // normal is copied first and scaled in place (GfComEnvSensor::flushGroundSingle's register order needs it)
    Plane(const Vec3& normal, const Vec3& pos) : normal(normal) {
        float length = this->normal.length();
        if (length <= 1e-6f) {
            this->normal = Vec3::zero;
        } else {
            float scale = 1.0f / length;
            this->normal.x = scale * this->normal.x;
            this->normal.y = scale * this->normal.y;
            this->normal.z = scale * this->normal.z;
        }
        d = -this->normal.dot(pos);
    }

    // facing normal (made length 1; one too short becomes zero) at distance d (BlackBoardField's wall plane)
    Plane(const Vec3& normal, float d) : normal(normal) {
        float length = this->normal.length();
        if (length <= 1e-6f) {
            this->normal = Vec3::zero;
        } else {
            float scale = 1.0f / length;
            this->normal.x = scale * this->normal.x;
            this->normal.y = scale * this->normal.y;
            this->normal.z = scale * this->normal.z;
        }
        this->d = d;
    }

    Vec3 normal;
    float d;
};

}  // namespace mm

#endif
