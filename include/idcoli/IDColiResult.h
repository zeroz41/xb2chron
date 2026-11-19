#ifndef IDCOLI_IDCOLIRESULT_H
#define IDCOLI_IDCOLIRESULT_H

#include "mm/Vec3.h"

namespace fw { class ColiCheckCallback; }
namespace idcoli { class IDCmfPoliData; }
namespace idcoli { class IDColiObj; }

namespace idcoli {
// one hit of a grand mesh test (IDColiGrandMesh's stock* steps copy it into the result, fw::ColiCheckCallback's
// coli_param_callback gets it). The field names are not the original's.
class IDColiCallArg {
public:
    mm::Vec3 m_pos;  // 0x0
    mm::Vec3 m_normal;  // 0x10
    mm::Vec3 m_vector;  // 0x20, the vecotr* step's (vecotrDef: zero unless the poli's flag 0x80 is set)
    const IDCmfPoliData* m_poli;  // 0x30
};

// a collision query's result, filled by the IDColiUtilColiResult tests and IDColiGrandMesh's stock* steps. The
// field names are not the original's.
class IDColiResult {
public:
    // inlined into IDColiDef's, IDColiPhantom's and IDColiCheckObj's constructors (same stores in all three)
    IDColiResult() {
        pad_d8 = nullptr;
        m_type = 0;
        m_tblMax = 0;
        m_nearLength = 100000.0f;
        m_tblNum = 0;
        m_ignoreMaterial = 0;
        m_secNearLength = -100000.0f;
        m_nearHit = false;
        m_secNearHit = false;
        pad_b2 = 0;
        m_calcVector = false;
        pad_f8 = nullptr;
        m_tblVector = nullptr;
        m_tblPoli = nullptr;
        m_tblPos = nullptr;
        m_tblNormal = nullptr;
        m_skipObj = nullptr;
        m_callback = nullptr;
    }

    int m_type;  // 0x0, IDColiGrandObj::testLine: 0 a check, 2 a table, else the nearest hits
    unsigned char pad_4[0xC];
    // the nearest hit (stockNear) and, for negative lengths, the second one (stockSecNear)
    IDColiCallArg m_near;  // 0x10
    IDColiCallArg m_secNear;  // 0x50
    float m_nearLength;  // 0x90
    void* m_nearObj;  // 0x98, m_obj when m_near was stored
    float m_secNearLength;  // 0xA0
    void* m_secNearObj;  // 0xA8
    bool m_nearHit;  // 0xB0, stockNear/stockTbl set it
    bool m_secNearHit;  // 0xB1
    unsigned char pad_b2;
    bool m_calcVector;  // 0xB3, IDColiGrandObj::testLine runs the vecotr* step only when it is set
    // stockTbl's tables (each may be null), filled up to m_tblMax
    mm::Vec3* m_tblPos;  // 0xB8
    mm::Vec3* m_tblNormal;  // 0xC0
    mm::Vec3* m_tblVector;  // 0xC8
    const IDCmfPoliData** m_tblPoli;  // 0xD0
    // 0xD8: IDColiMove::moveColi points it at a bit per hit (three words), its test* functions clear them
    unsigned int* pad_d8;
    unsigned int m_tblNum;  // 0xE0
    unsigned int m_tblMax;  // 0xE4
    // 0xE8, the materials the query skips: an object whose m_materialBit shares a bit is not tested
    unsigned int m_ignoreMaterial;
    unsigned char pad_ec[4];
    void* m_obj;  // 0xF0, the object under test (the stock* steps record it with a hit)
    // 0xF8: the constructor and IDColiCheckObj's tests clear it, which then point it at the object under test
    const IDColiObj* pad_f8;
    fw::ColiCheckCallback* m_callback;  // 0x100, stockTbl hands it every stored hit
    // 0x108, an object the query skips: IDColiObjGrdChar::test* return false when their owner is it (the name is
    // not the original's)
    IDColiObj* m_skipObj;
};
}  // namespace idcoli

#endif
