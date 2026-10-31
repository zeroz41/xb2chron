#ifndef IDCOLI_IDCOLIGRANDMESH_H
#define IDCOLI_IDCOLIGRANDMESH_H

#include "mm/Mat44.h"

namespace idcoli { class IDColiCallArg; }
namespace idcoli { class IDCmfPoliData; }
namespace idcoli { class IDColiInput; }
namespace idcoli { class IDColiResult; }

namespace idcoli {

// one position record of a grand mesh's work (0xA0 bytes: IDColiGrandTree's inst*Hit index them so).
// IDColiPrimitive::calcPosDataSetup fills it from a matrix and two corners; the names are not the original's.
class IDCmfPosData {
public:
    mm::Mat44 m_matrix;  // 0x0, the matrix transposed (the translation in column 3)
    mm::Mat44 m_invMatrix;  // 0x40, the inverse
    mm::Vec3 m_max;  // 0x80, the bounding box of the transformed corners
    mm::Vec3 m_min;  // 0x90
};

// the info record beside each IDCmfPosData (4 bytes: inst*Hit index them so). Fields are not declared yet.
class IDCmfPosInfo {
public:
    unsigned char pad_0[4];
};

// a grand mesh's work (IDColiGrandObj's constructor takes it); the names are not the original's
class wrkIDCmfWork {
public:
    unsigned char pad_0[0x30];
    const IDCmfPosData* m_posData;  // 0x30, inst*Hit index it
    const IDCmfPosInfo* m_posInfo;  // 0x38, the same index
};

// the mesh tests of a grand object. IDColiGrandObj::testLine/testRay/... store the result at 0x8 and the input at
// 0x10 and then run IDColiGrandMesh's and IDColiGrandTree's members on the same object through member pointers, so
// both read this layout (IDColiGrandObj's relation to them is not declared yet). The names are not the original's.
class IDColiGrandMesh {
public:
    // whether a hit at that distance counts for the query kind
    bool lenghtLine(float length);
    bool lenghtRay(float length);
    bool lenghtSphere(float length);
    bool lenghtWallSphere(float length);
    void vecotrNon(IDColiCallArg& arg, const IDCmfPoliData* poli);
    // store a hit in the result: the nearest (stockNear), the nearest and the second one for negative lengths
    // (stockSecNear), the next table entry (stockTbl); then run the m_vecotr step on it
    void stockNear(IDColiCallArg& arg, const IDCmfPoliData* poli, float length);
    void stockSecNear(IDColiCallArg& arg, const IDCmfPoliData* poli, float length);
    void stockTbl(IDColiCallArg& arg, const IDCmfPoliData* poli, float length);

    wrkIDCmfWork* m_work;  // 0x0
    IDColiResult* m_result;  // 0x8
    const IDColiInput* m_input;  // 0x10
    unsigned char pad_18[0x58];
    // the vector step IDColiGrandObj::testLine picks (vecotrNon, vecotrDef or vecotrInst) and the one for instances
    void (IDColiGrandMesh::*m_vecotr)(IDColiCallArg& arg, const IDCmfPoliData* poli);  // 0x70
    void (IDColiGrandMesh::*m_vecotrInst)(IDColiCallArg& arg, const IDCmfPoliData* poli);  // 0x80
};

class IDColiGrandTree : public IDColiGrandMesh {
public:
    bool instLineHit(unsigned int index);
    bool instLineHitParts(const IDCmfPosData* posData, const IDCmfPosInfo* posInfo);
    bool instRayHit(unsigned int index);
    bool instRayHitParts(const IDCmfPosData* posData, const IDCmfPosInfo* posInfo);
    bool instSphereHit(unsigned int index);
    bool instSphereHitParts(const IDCmfPosData* posData, const IDCmfPosInfo* posInfo);
    bool instCapsuleHit(unsigned int index);
    bool instCapsuleHitParts(const IDCmfPosData* posData, const IDCmfPosInfo* posInfo);
    // whether the box (max, min) lies apart from the input's box (the parameter names are not the original's)
    bool isAaBbToAaBb(const float* max, const float* min);
};

}  // namespace idcoli

#endif
