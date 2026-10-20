#ifndef CLASSES_MM_SPHERE_H
#define CLASSES_MM_SPHERE_H

#include "classes/mm/PrimBase.h"

namespace mm { class Aabb; }
namespace mm { class Obb; }
namespace mm { class PrimBase; }

namespace mm {
// table 0x7100B77428
class Sphere : public ::mm::PrimBase {
public:
    virtual ~Sphere();  // slot 0
    virtual void getOBB(mm::Obb&) const;  // slot 2
    virtual void getAABB(mm::Aabb&) const;  // slot 3
    virtual void isCollide(mm::PrimBase const&) const;  // slot 6
};
}  // namespace mm

#endif
