#ifndef IDCOLI_IDCOLIDEF_H
#define IDCOLI_IDCOLIDEF_H

#include "idcoli/IDColiResult.h"
#include "mm/Vec3.h"

namespace idcoli {
class IDColiObj;

// a collision query against the ground (IDColiManager.cpp): callers build one on the stack, set the result's kind
// and the two leading options, call one test* and read m_result. Size 0x120 (ptlib::ParticleManager's frames). The
// field names are not the original's.
class IDColiDef {
public:
    IDColiDef();
    bool testLine(const mm::Vec3& start, const mm::Vec3& end);
    bool testRay(const mm::Vec3& pos, const mm::Vec3& dir, float, float);
    bool testSphere(const mm::Vec3& pos, float radius);
    bool testCapsule(const mm::Vec3& start, const mm::Vec3& end, float radius);
    bool testCharColiObj(IDColiObj* pObj, float);

    bool pad_0;  // 0x0: the constructor clears it; ParticleManager's tests clear it again
    bool pad_1;  // 0x1: the constructor sets it; ParticleManager's tests set it again
    bool pad_2;  // 0x2: the constructor sets it
    unsigned char pad_3;
    int pad_4;    // 0x4: the constructor clears it
    void* pad_8;  // 0x8: the constructor clears it
    IDColiResult m_result;  // 0x10
};
}  // namespace idcoli

#endif
