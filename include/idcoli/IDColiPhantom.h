#ifndef IDCOLI_IDCOLIPHANTOM_H
#define IDCOLI_IDCOLIPHANTOM_H

#include "idcoli/IDColiResult.h"
#include "mm/Vec3.h"

namespace idcoli {
class IDColiObj;

// a collision query against the phantoms (IDColiManager.cpp): built on the stack like IDColiDef, whose layout its
// constructor shares (fw::ColiCheck sets both the same way). The field names are not the original's.
class IDColiPhantom {
public:
    IDColiPhantom();
    bool testLine(const mm::Vec3& start, const mm::Vec3& end);
    bool testSphere(const mm::Vec3& pos, float radius);
    bool testCapsule(const mm::Vec3& start, const mm::Vec3& end, float radius);
    bool testCharColiObj(IDColiObj* pObj, float);
    bool testPhantomColiObj(IDColiObj* pObj, float);

    bool pad_0;  // 0x0: the constructor clears it
    bool pad_1;  // 0x1: the constructor sets it
    bool pad_2;  // 0x2: the constructor sets it
    unsigned char pad_3;
    float m_radiusSq;                   // 0x4: fw::ColiCheck's tests store the config's radius squared
    fw::ColiCheckCallback* m_callback;  // 0x8: fw::ColiCheck's tests point it at their ColiCheckCallback
    IDColiResult m_result;              // 0x10
};
}  // namespace idcoli

#endif
