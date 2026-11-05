#ifndef IDCOLI_IDCOLIINPUT_H
#define IDCOLI_IDCOLIINPUT_H

#include "mm/Vec3.h"

namespace idcoli {

// a collision query's input. IDColiUtilColi{Simple,Result}'s statics hand the shape it holds at 0xB0 to the
// shape tests as the work of the shape their name gives (sphere, capsule, box, line or ray). Later fields are not
// declared yet; the names are not the original's.
class IDColiInput {
public:
    const void* getShape() const { return m_shape; }
    void* getShape() { return m_shape; }

    // the query's bounding box (IDColiGrandTree::isAaBbToAaBb tests a box against it); the names are not the
    // original's. Vec3s: IDColiGrandObj::coliCallCheck hands both to IDColiUtilTreeAcc::startTreeAaBbMode.
    mm::Vec3 m_max;  // 0x0
    mm::Vec3 m_min;  // 0x10
    // IDColiInputUtil's get* fill the following from the query's points (the names are not the original's):
    // the position (a sphere's centre, a line's or ray's start) and the line's or ray's vector (end - start)
    mm::Vec3 m_pos;  // 0x20
    mm::Vec3 m_dir;  // 0x30
    // the line of a line/ray query as IDColiGrandTree::isLineAaBb's separating-axis test reads it: its middle point,
    // its half vector and that vector's absolute values (the names are not the original's)
    mm::Vec3 m_lineCenter;  // 0x40
    mm::Vec3 m_lineHalf;  // 0x50
    mm::Vec3 m_lineHalfAbs;  // 0x60
    // the start and end points getLine/getRay/getCapsule are given (the names are not the original's)
    mm::Vec3 m_start;  // 0x70
    mm::Vec3 m_end;  // 0x80
    // the hit distance range (IDColiGrandMesh's lenght* tests: a ray hit lies in [m_lengthMin, m_lengthMax], a
    // sphere's within m_lengthMax); the names are not the original's
    float m_lengthMax;  // 0x90
    float m_lengthMin;  // 0x94
    float m_length;  // 0x98, the length of m_dir (getLine/getCapsule; getRay sets 1); the name is not the original's
    unsigned char pad_9c[4];
    // 0xA0, when non-zero IDColiGrandTree's inst*HitParts skip instances whose box's half diagonal squared is not
    // above it (the name is not the original's)
    float m_instSizeMin;
    // 0xA4, the bounding box rounded out to whole units (ceil of m_max, floor of m_min), as IDColiInputUtil's get*
    // store it; the names are not the original's
    short m_intMax[3];
    short m_intMin[3];
    // 0xB0, the work of the query's shape (CLSphereWork, CLLineWork, CLRayWork, CLBoxWork or CLCapsuleWork): 0xE0 is
    // the largest (a ray's). 0x190 bytes: IDColiObjGrdChar::test* keep one on the stack 0x190 bytes below the frame's end
    unsigned char m_shape[0xE0];
};

}  // namespace idcoli

#endif
