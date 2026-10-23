#ifndef FW_PRIM_H
#define FW_PRIM_H

#include "mm/Vec3.h"
#include "mm/Line2.h"

namespace fw {
// a sphere: its center and radius (the field names are not the original's)
class PrimSphere {
public:
    void setup(const mm::Vec3& center, float radius);

    mm::Vec3 m_center;
    float m_radius;
};

// a capsule: a segment and a radius (the field names are not the original's)
class PrimCapsule : public mm::Line2 {
public:
    void setup(const mm::Vec3& start, const mm::Vec3& end, float radius);
    // whether it touches another capsule, a sphere
    bool isCollide(const PrimCapsule& other) const;
    bool isCollide(const PrimSphere& sphere) const;

    float m_radius;
};
}  // namespace fw

#endif
