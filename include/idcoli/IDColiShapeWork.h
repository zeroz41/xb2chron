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
    // the matrix's rotation rows transposed (calcBaseBoxSetup), their inverse
    mm::Vec3 m_axes[3];  // 0x0
    mm::Vec3 m_invAxes[3];  // 0x30
    mm::Vec3 m_center;  // 0x60
    // the half extents (calcBoxAaBb transforms the 8 corners +-size); createBaPosBox's radius and height are x, y
    mm::Vec3 m_size;  // 0x70
    // the bounding box (IDColiPrimitive::createAaBbBox widens a box by them; createBaseInBox grows them by 4)
    mm::Vec3 m_max;  // 0x80
    mm::Vec3 m_min;  // 0x90
    float m_scale;  // 0xA0, the matrix's axis length * IDColiObj::OBJ_CALC_RADIUS (calcBaseBoxSetup)
    float m_invScale;  // 0xA4
};

// a capsule shape's work (IDColiPrimitive::createBaPosCapsule/createAaBbCapsule read it); the names are not the
// original's
class CLCapsuleWork {
public:
    mm::Vec3 m_pos;  // 0x0, createBaPosCapsule's position
    mm::Vec3 m_end;  // 0x10, the other end (calcCapsuleSetup: m_offset = m_end - m_pos)
    mm::Vec3 m_offset;  // 0x20, createBaPosCapsule's offset
    mm::Vec3 m_max;  // 0x30, the bounding box (createAaBbCapsule)
    mm::Vec3 m_min;  // 0x40
    float m_radius;  // 0x50
    float m_lengthSq;  // 0x54, createBaPosCapsule's height is its square root plus twice the radius
    float m_invLengthSq;  // 0x58 (calcCapsuleSetup)
};

// a sub character's work (IDColiPrimitive::createSubBaseCharacter): a capsule work (a sphere work in its place when
// the shape is too short for a capsule) followed by the move of its position since the previous build (cleared when
// the flag is set or the move is 2 or longer). The class and member names are not the original's.
class CLSubCharacterWork : public CLCapsuleWork {
public:
    mm::Vec3 m_move;  // 0x60
};

// a line shape's work: 0x70 bytes (1.0.0's IDColiPrimitive::createRay fills two of them, at 0x0 and 0x70 of a
// CLRayWork). IDColiInputUtil::getLine fills it; the names are not the original's.
class CLLineWork {
public:
    mm::Vec3 m_start;  // 0x0
    mm::Vec3 m_end;  // 0x10
    mm::Vec3 m_dir;  // 0x20, m_end - m_start
    mm::Vec3 m_unitDir;  // 0x30, m_dir over its length (x 0, y 1 when it is too short)
    mm::Vec3 m_max;  // 0x40, the bounding box
    mm::Vec3 m_min;  // 0x50
    float m_lengthSq;  // 0x60
    float m_length;  // 0x64
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
