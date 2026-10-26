#ifndef IDCOLI_IDCOLISHAPEWORK_H
#define IDCOLI_IDCOLISHAPEWORK_H

#include "mm/Vec3.h"

namespace idcoli {

// a sphere shape's work (IDColiPrimitive::createBaPosSphere reads it); the names are not the original's
class CLSphereWork {
public:
    mm::Vec3 m_center;  // 0x0
    float m_radius;  // 0x10
};

// a box shape's work (IDColiPrimitive::createBaPosBox reads it); the names are not the original's
class CLBoxWork {
public:
    unsigned char pad_0[0x60];
    mm::Vec3 m_center;  // 0x60
    float m_radius;  // 0x70
    float m_height;  // 0x74
};

// a line shape's work: 0x70 bytes (1.0.0's IDColiPrimitive::createRay fills two of them, at 0x0 and 0x70 of a
// CLRayWork). Fields are not declared yet.
class CLLineWork {
public:
    unsigned char pad_0[0x70];
};

// a ray shape's work: two line works (1.0.0's IDColiPrimitive::createRay(CLRayWork&, ...) writes both; the ray
// tests run the line test on the first with the ray flag clear, then on the second with it set). The name of the
// member is not the original's.
class CLRayWork {
public:
    CLLineWork m_lines[2];
};

}  // namespace idcoli

#endif
