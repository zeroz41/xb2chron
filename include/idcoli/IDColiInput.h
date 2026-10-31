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

    // the query's bounding box (IDColiGrandTree::isAaBbToAaBb tests a box against it); the names are not the
    // original's. Vec3s: IDColiGrandObj::coliCallCheck hands both to IDColiUtilTreeAcc::startTreeAaBbMode.
    mm::Vec3 m_max;  // 0x0
    mm::Vec3 m_min;  // 0x10
    unsigned char pad_20[0x20];
    // the line of a line/ray query as IDColiGrandTree::isLineAaBb's separating-axis test reads it: its middle point,
    // its half vector and that vector's absolute values (the names are not the original's)
    mm::Vec3 m_lineCenter;  // 0x40
    mm::Vec3 m_lineHalf;  // 0x50
    mm::Vec3 m_lineHalfAbs;  // 0x60
    unsigned char pad_70[0x20];
    // the hit distance range (IDColiGrandMesh's lenght* tests: a ray hit lies in [m_lengthMin, m_lengthMax], a
    // sphere's within m_lengthMax); the names are not the original's
    float m_lengthMax;  // 0x90
    float m_lengthMin;  // 0x94
    unsigned char pad_98[8];
    // 0xA0, when non-zero IDColiGrandTree's inst*HitParts skip instances whose box's half diagonal squared is not
    // above it (the name is not the original's)
    float m_instSizeMin;
    unsigned char pad_a4[0xC];
    unsigned char m_shape[0x38];  // 0xB0 (0xE8 is the next field the callers read)
    // 0x190 bytes: IDColiObjGrdChar::test* keep one on the stack 0x190 bytes below the frame's end
    unsigned char pad_e8[0xA8];
};

}  // namespace idcoli

#endif
