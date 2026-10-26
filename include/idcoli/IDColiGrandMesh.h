#ifndef IDCOLI_IDCOLIGRANDMESH_H
#define IDCOLI_IDCOLIGRANDMESH_H

namespace idcoli { class IDColiCallArg; }
namespace idcoli { class IDCmfPoliData; }
namespace idcoli { class IDColiInput; }
namespace idcoli { class IDColiResult; }

namespace idcoli {

// one position record of a grand mesh's work (0xA0 bytes: IDColiGrandTree's inst*Hit index them so). Fields are not
// declared yet.
class IDCmfPosData {
public:
    unsigned char pad_0[0xA0];
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

    wrkIDCmfWork* m_work;  // 0x0
    IDColiResult* m_result;  // 0x8
    const IDColiInput* m_input;  // 0x10
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
};

}  // namespace idcoli

#endif
