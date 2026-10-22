#include "mm/Vec3.h"

namespace mm {

// Three Vec3 constants at file scope that only this file's static initializer touches (no code reads them):
// copies of Vec3::zero and Vec3::unitY, then (0, -1, 0). No symbol names them in either version, and 1.0.0's
// copy of this initializer is mm_cylinder.cpp's. The names are not the original's.
static const Vec3 s_unkVec3A = Vec3::zero;
static const Vec3 s_unkVec3B = Vec3::unitY;
static const Vec3 s_unkVec3C(0.0f, -1.0f, 0.0f);

}  // namespace mm
