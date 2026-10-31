#ifndef CLASSES_MM_SPHERE_H
#define CLASSES_MM_SPHERE_H

#include "classes/mm/PrimBase.h"
#include "mm/Aabb.h"
#include "mm/MMStdBase.h"
#include "mm/Obb.h"

// mm_lib's mm_math/mm_sphere.h as monolib_mm's include path names it (isCollide's assert cites it so)
#define MM_SPHERE_PATH \
    "D:/Monolithsoft/BF2/prog/libs/monolib_mm/proj/windows/../../../MCL/mm_lib/source\\mm_math/mm_sphere.h"

namespace mm {
// table 0x7100B77428. Its members are inline in mm_sphere.h; the table and the inline slots are emitted in
// th_dev_file_nx, so the destructor is defined there.
class Sphere : public ::mm::PrimBase {
public:
    virtual ~Sphere();  // slot 0
    virtual void getOBB(mm::Obb&) const;  // slot 2
    // the box from getPos() - radius to getPos() + radius
    virtual void getAABB(mm::Aabb& aabb) const {
        Vec3 max;
        Vec3 min;
        {
            const Vec3& center = getPos();
            float radius = getRadius();
            max.x = radius + center.x;
            max.y = radius + center.y;
            max.z = radius + center.z;
        }
        {
            const Vec3& center = getPos();
            float radius = getRadius();
            min.x = center.x - radius;
            min.y = center.y - radius;
            min.z = center.z - radius;
        }
        aabb.set(max, min);
    }
    // a sphere tests itself; the other kinds test against it
    virtual bool isCollide(const PrimBase& prim) const {  // slot 6
        switch (prim.getType()) {
        case PRIM_TYPE_0:
            return prim.isCollide(*this);
        case PRIM_TYPE_1:
            return prim.isCollide(*this);
        case PRIM_SPHERE:
            return isCollideSphere(*this);
        default:
            return false;
        }
    }

    float getRadius() const { return m_size.x; }

    // whether prim (a sphere) overlaps this one (isCollide passes itself; the name is not the original's)
    bool isCollideSphere(const PrimBase& prim) const {
#line 321 MM_SPHERE_PATH
        MM_ASSERT(prim.getType()==PRIM_SPHERE);
        const Sphere& sphere = static_cast<const Sphere&>(prim);
        Vec3 d = getPos() - sphere.getPos();
        float distSq = d.x * d.x + d.y * d.y + d.z * d.z;
        float r = getRadius() + sphere.getRadius();
        return distSq < r * r;
    }
};
}  // namespace mm

#endif
