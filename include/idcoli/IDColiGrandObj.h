#ifndef IDCOLI_IDCOLIGRANDOBJ_H
#define IDCOLI_IDCOLIGRANDOBJ_H

#include "classes/idcoli/IDColiObjBase.h"
#include "mm/Mat44.h"

namespace idcoli {

// one moving part of a grand object (0x200 bytes: IDColiParmsGrand::getMoveObj indexes them so). Only the members
// IDColiParmsGrand/IDColiPartsMoveGrand use are declared; the field names are not the original's.
class IDColiGrdMoveObj {
public:
    void setMat(const mm::Mat44& matrix);
    void update();

    // the matrix per frame half (setMat writes [IDColiManager::s_nStkIdx] and marks that half in m_matRequest)
    mm::Mat44 m_mats[2];  // 0x0
    unsigned char pad_80[0x100];
    // the bounds IDColiObjGrand::update enters into its tree (setupTreeList's max, min)
    mm::Vec3 m_max;  // 0x180
    mm::Vec3 m_min;  // 0x190
    unsigned char pad_1a0[0x10];
    const char* m_name;  // 0x1B0, IDColiParmsGrand::getMoveObjIdx compares it
    void* m_userData;  // 0x1B8, IDColiPartsMoveGrand::setUserData
    unsigned short m_matRequest;  // 0x1C0, 1 << s_nStkIdx per half setMat wrote
    unsigned char pad_1c2[6];
    // its entry per tree (IDColiObjGrand::update enters the one of the tree it builds)
    IDColiTreeObj m_treeObjs[2];  // 0x1C8
    unsigned char pad_1f8[8];
};

// the destructor (its owners' destructors call it; its body is empty) and the fields IDColiParmsGrand reads; the
// field names are not the original's
class IDColiGrandObj {
public:
    ~IDColiGrandObj();

    unsigned char pad_0[0x70];
    IDColiGrdMoveObj* m_moveObjs;  // 0x70
    int m_moveObjNum;  // 0x78
};

}  // namespace idcoli

#endif
