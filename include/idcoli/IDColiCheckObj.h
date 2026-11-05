#ifndef IDCOLI_IDCOLICHECKOBJ_H
#define IDCOLI_IDCOLICHECKOBJ_H

#include "idcoli/IDColiResult.h"
#include "mm/Vec3.h"

namespace idcoli {
class IDColiObj;

// a collision query against one collision object (IDColiManager.cpp): built on the stack like IDColiDef, whose layout its
// constructor shares (fw::ColiCheck sets both the same way). The field names are not the original's.
class IDColiCheckObj {
public:
    IDColiCheckObj();
    bool testLine(const IDColiObj* obj, const mm::Vec3& start, const mm::Vec3& end);
    bool testSphere(const IDColiObj* obj, const mm::Vec3& pos, float radius);

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
