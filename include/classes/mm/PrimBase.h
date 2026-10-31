#ifndef CLASSES_MM_PRIMBASE_H
#define CLASSES_MM_PRIMBASE_H

#include "mm/Quat.h"
#include "mm/Vec3.h"

namespace mm { class Aabb; }
namespace mm { class Obb; }

namespace mm {
// a primitive's kind at 0x40. Only PRIM_SPHERE's name is known (mm_sphere.h's assert
// "prim.getType()==PRIM_SPHERE"); the other two are placeholders.
enum PRIM_TYPE : int {
    PRIM_TYPE_0,
    PRIM_TYPE_1,
    PRIM_SPHERE,
};

// table none (its derived classes'). ScnDebugManipuRot builds a Sphere with m_pos Vec3::zero, m_rot
// Quat::identity, m_size (1, 1, 1) and m_type PRIM_SPHERE.
class PrimBase {
public:
    // slot 0; out of line in th_dev_file_nx (its D2 follows DebDraw::renderSquare; Sphere's D1 is that D2)
    virtual ~PrimBase();
    virtual void getOBB(mm::Obb&) const = 0;  // slot 2
    virtual void getAABB(mm::Aabb&) const = 0;  // slot 3
    virtual const Vec3& getPos() const { return m_pos; }  // slot 4
    virtual const Quat& getRot() const { return m_rot; }  // slot 5
    virtual bool isCollide(const PrimBase& prim) const = 0;  // slot 6 (Sphere::isCollide calls it on prim)

    PRIM_TYPE getType() const { return m_type; }

    // the names below are not the original's
    Vec3 m_pos;        // 0x10
    Quat m_rot;        // 0x20
    Vec3 m_size;       // 0x30 Sphere's radius is its x; Sphere::getOBB passes it as the box's size
    PRIM_TYPE m_type;  // 0x40
};
}  // namespace mm

#endif
