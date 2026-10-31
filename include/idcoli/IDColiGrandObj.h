#ifndef IDCOLI_IDCOLIGRANDOBJ_H
#define IDCOLI_IDCOLIGRANDOBJ_H

#include "classes/idcoli/IDColiObjBase.h"
#include "idcoli/IDColiGrandMesh.h"
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
    unsigned char pad_80[0x80];
    // its position record: IDColiGrandObj::coliCallCheck passes it and m_posInfo to the instance test; its bounds
    // are what IDColiObjGrand::update enters into its tree (setupTreeList's max, min)
    IDCmfPosData m_posData;  // 0x100
    IDCmfPosInfo m_posInfo;  // 0x1A0
    unsigned char pad_1a4[0xC];
    const char* m_name;  // 0x1B0, IDColiParmsGrand::getMoveObjIdx compares it
    // IDColiPartsMoveGrand::setUserData; IDColiGrandObj::coliCallCheck makes it the result's object
    void* m_userData;  // 0x1B8
    unsigned short m_matRequest;  // 0x1C0, 1 << s_nStkIdx per half setMat wrote
    unsigned char pad_1c2[6];
    // its entry per tree (IDColiObjGrand::update enters the one of the tree it builds)
    IDColiTreeObj m_treeObjs[2];  // 0x1C8
    unsigned char pad_1f8[8];
};

// the collision test of a grand object: IDColiDef/IDColiMove/IDColiCheckObj build one on the stack over the
// object's wrkIDCmfWork, call one test* and destroy it. Each test* stores the result and the input and picks the
// IDColiGrandMesh/IDColiGrandTree steps for the query kind, then runs coliCallCheck (a check: the first hit ends it)
// or coliCallResl/coliMoveCallResl (collect hits). The parameter names are not the original's.
class IDColiGrandObj : public IDColiGrandTree {
public:
    IDColiGrandObj(wrkIDCmfWork* work);
    ~IDColiGrandObj();
    bool testLine(IDColiResult& result, const IDColiInput& input);
    bool testRay(IDColiResult& result, const IDColiInput& input);
    bool testSphere(IDColiResult& result, const IDColiInput& input, bool wall);
    bool testCapsule(IDColiResult& result, const IDColiInput& input, bool wall);
    bool testMoveSphere(IDColiResult& result, const IDColiInput& input, bool wall);
    bool testMoveCapsule(IDColiResult& result, const IDColiInput& input, bool wall);
    bool coliCallCheck(bool (IDColiGrandTree::*parts)(const IDCmfPosData* posData, const IDCmfPosInfo* posInfo));
    bool coliCallResl(bool (IDColiGrandTree::*parts)(const IDCmfPosData* posData, const IDCmfPosInfo* posInfo));
    bool coliMoveCallResl(bool (IDColiGrandTree::*parts)(const IDCmfPosData* posData, const IDCmfPosInfo* posInfo),
                          bool wall);
};

}  // namespace idcoli

#endif
