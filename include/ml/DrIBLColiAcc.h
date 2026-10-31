#ifndef ML_DRIBLCOLIACC_H
#define ML_DRIBLCOLIACC_H

#include "mm/Vec3.h"

namespace ml {
// the IBL collision tests (DrIBLMan::update calls testTreeInvalidColi). Like DrEnvColiObj's tests, but each shape
// carries its own axes: a box/cylinder is a 3x4 float matrix (axes in columns 0..2 of rows 0x0/0x10/0x20, centre at
// 0x30, bounding radius 0x3C) and half extents at 0x40..0x48; a sphere/unrotated shape has its centre at 0x0, radius
// 0xC and half extents at 0x10..0x18. Only what this unit's functions use is declared.
class DrIBLColiAcc {
public:
    bool envcoli_box(const unsigned char* data, const mm::Vec3& pos, float range);
    bool envcoli_sphere(const unsigned char* data, const mm::Vec3& pos, float range);
    bool envcoli_cylinder(const unsigned char* data, const mm::Vec3& pos, float range);
    bool envcoli_notrot_box(const unsigned char* data, const mm::Vec3& pos, float range);
    bool envcoli_notrot_cylinder(const unsigned char* data, const mm::Vec3& pos, float range);

    // the test of each shape type (testTreeColi and testTreeInvalidColi call through it)
    static bool (DrIBLColiAcc::*s_pColiTest[5])(const unsigned char*, const mm::Vec3&, float);
};
}  // namespace ml

#endif
