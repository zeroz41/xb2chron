#ifndef CLASSES_IDCOLI_IDCOLIOBJBASE_H
#define CLASSES_IDCOLI_IDCOLIOBJBASE_H

#include "classes/idcoli/IDColiObj.h"
#include "mm/Mat44.h"
#include "mm/Vec3.h"

namespace idcoli { class IDColiTreeTop; }

namespace idcoli {
// the axis a sweep-and-prune list sorts on (IDColiObjBase::sweepTreeMax indexes its per-axis lists with it)
enum IdSweepAxisType {};
// a component of a vector (x, y, z)
enum IdVectorAxisType {};
// a shape's base type (the IDColiPrimitive creators write it; 0 a sphere)
// an object's base shape kind: the index of the IDColiUtilColi tables (their entries name the shape each index
// tests against: sphere, box, capsule, capsule, sphere, poli, in-box, in-capsule) and the value the IDColiPrimitive
// creators store. The enumerator names are not the original's.
enum IDColiBaseType {
    IDCOLI_BASE_SPHERE,
    IDCOLI_BASE_BOX,
    IDCOLI_BASE_CAPSULE,
    IDCOLI_BASE_CHARACTER,
    IDCOLI_BASE_SUB_CHARACTER,
    IDCOLI_BASE_POLI,
    IDCOLI_BASE_IN_BOX,
    IDCOLI_BASE_IN_CAPSULE,
};

// an object's link in a cell list of its IDColiTreeTop (the names are not the original's)
class IDColiTreeObj {
public:
    IDColiTreeObj* m_prev;  // 0x0
    IDColiTreeObj* m_next;  // 0x8
    unsigned char pad_10[8];
};

// table 0x7100B7F0F0
// the fields IDColiParmsBase and the shape creators of IDColiParmsCharacter/IDColiParmsPhantom reach (0x1D0 bytes:
// IDColiManager::createColiPhantom allocates its IDColiObjPhantomCheck so). The names are not the original's.
class IDColiObjBase : public ::idcoli::IDColiObj {
public:
    // the ; keeps the table store clang skips for an empty body
    virtual ~IDColiObjBase() { ; }  // slot 0
    void sweepPush(IDColiObjBase* next);
    void sweepPop();
    void sweepTreeMax(IdSweepAxisType axis, IdVectorAxisType component);
    void releaseDefTree();

    mm::Vec3 m_max;  // 0x50, IDColiParmsBase::getMax
    mm::Vec3 m_min;  // 0x60, IDColiParmsBase::getMin
    mm::Mat44 m_matrix;  // 0x70, IDColiParmsBase::setMatrix
    mm::Vec3 m_size;  // 0xB0, the shape's extents (a sphere's radius in all three)
    int m_shapeType;  // 0xC0, 0 sphere, 1 box, 2 capsule, 3 character, 6/7 the box/capsule with flag 0x400
    IDColiBaseType m_baseType;  // 0xC4, indexes the IDColiUtilColi tables
    unsigned int m_offMaterialBit;  // 0xC8, IDColiParmsBase::setOffMaterialBit
    unsigned char pad_cc[4];
    unsigned char m_base[0xB0];  // 0xD0, the shape built from m_matrix and m_size (the IDColiPrimitive creators)
    float m_sweepMax[2];  // 0x180, per sweep axis (sweepTreeMax)
    IDColiObjBase* m_sweepPrev[2];  // 0x188, per sweep axis (sweepPush/sweepPop)
    IDColiObjBase* m_sweepNext[2];  // 0x198
    IDColiTreeTop* m_tree;  // 0x1A8
    IDColiTreeObj m_treeObj;  // 0x1B0
    int m_treeIndex;  // 0x1C8, the cell of m_tree holding m_treeObj (-1 none)
    int m_priority;  // 0x1CC, IDColiParmsBase::setPriority
};
}  // namespace idcoli

#endif
