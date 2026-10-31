#ifndef IDCOLI_IDCOLIGRANDMESH_H
#define IDCOLI_IDCOLIGRANDMESH_H

#include "mm/Mat44.h"
#include "mm/Vec3NA.h"

namespace idcoli { class IDColiCallArg; }
namespace idcoli { class IDColiInput; }
namespace idcoli { class IDColiResult; }
namespace idcoli { class IDColiGrdMoveObj; }
namespace idcoli { class IDColiTreeTop; }

namespace idcoli {

// a polygon of the grand data (12 bytes: meshLine indexes the table at wrkIDCmfWork 0x10 so; IDColiCallArg::m_poli
// points to one). Only what vecotrDef/vecotrInst read is declared; the names are not the original's.
class IDCmfPoliData {
public:
    unsigned int m_offset;  // 0x0, its index record's offset in the grand data (u16 indices)
    // the number of vertex indices at the head of the index record (meshLine loops over them)
    unsigned char m_num;  // 0x4
    // which table of wrkIDCmfWork::m_vectors (and of the normal tables at 0x18, in meshLine) the record indexes
    unsigned char m_table;  // 0x5
    unsigned char pad_6[2];
    unsigned short m_flags;  // 0x8, bit 7: it has a vector (vecotrDef/vecotrInst give zero otherwise)
    unsigned char pad_a[2];
};

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

// a grand object's work: IDColiObjGrand holds it at 0x50 (IDColiParmsGrand's constructor and IDColiDef's tests take
// that address; createGrand fills it, coliCallCheck and getGrandAABB read it). The names are not the original's.
class wrkIDCmfWork {
public:
    // the bounding box record of the grand data (getGrandAABB widens by it); the name is not the original's
    struct Box {
        float m_max[3];  // 0x0
        float m_min[3];  // 0xC
    };
    // the head of the grand data IDColiObjGrand::createGrand takes (it sizes the work from the counts at
    // 0x1C..0x3C and 0x94); only what getGrandAABB reads is declared. The names are not the original's.
    struct Header {
        unsigned char pad_0[8];
        unsigned int m_size;  // 0x8, the box record sits 0x28 bytes before it unless m_flags bit 1 is set
        unsigned char pad_c[0x7C];
        unsigned char m_flags;  // 0x88, bit 1: m_boxOffset holds the box record's offset
        unsigned char pad_89[3];
        unsigned int m_boxOffset;  // 0x8C
    };

    const Header* m_data;  // 0x0, createGrand's data
    unsigned char pad_8[0x20];
    // the vector tables (vecotrDef/vecotrInst pick one by IDCmfPoliData's table byte)
    const mm::Vec3NA* const* m_vectors;  // 0x28
    const IDCmfPosData* m_posData;  // 0x30, inst*Hit index it
    const IDCmfPosInfo* m_posInfo;  // 0x38, the same index
    unsigned char pad_40[0x30];
    // the moving parts (0x200 bytes each); IDColiObjGrand::update updates them and enters them into a tree
    IDColiGrdMoveObj* m_moveObjs;  // 0x70
    int m_moveObjNum;  // 0x78
    unsigned char pad_7c[4];
    // the instances of the grand data (IDColiGrandObj::coliCallCheck runs m_treeHit on each m_index whose id is
    // not a global one (IDColiManager::isGblId) and whose m_flags bit 0 is clear or bits 8.. equal the manager's
    // m_subNum). The names are not the original's.
    struct Inst {
        unsigned int m_id;  // 0x0
        unsigned int m_index;  // 0x4
        unsigned short m_flags;  // 0x8
        unsigned char pad_a[6];
    };
    const Inst* m_insts;  // 0x80
    int m_instNum;  // 0x88
    unsigned char pad_8c[4];
    // createGrand destroys both (without freeing them) while m_memBlock is set, then frees m_memBlock
    IDColiTreeTop* m_treeTops[2];  // 0x90
    // the tree IDColiObjGrand::update builds is m_treeTops[m_bank == 0]; update then makes it m_bank
    int m_bank;  // 0xA0
    unsigned char pad_a4[4];
    void* m_memBlock;  // 0xA8, IDColiObjGrand's constructor clears it
};

// the mesh tests of a grand object (IDColiGrandObj derives from it through IDColiGrandTree: its testLine/testRay/...
// store the result at 0x8, the input at 0x10 and the member pointers below, then run them). The names are not the
// original's.
class IDColiGrandMesh {
public:
    // test the mesh's polygons of a tree cell (the parameter name is not the original's)
    bool meshLine(unsigned int index);
    bool meshSphere(unsigned int index);
    bool meshCapsule(unsigned int index);
    // whether a hit at that distance counts for the query kind
    bool lenghtLine(float length);
    bool lenghtRay(float length);
    bool lenghtSphere(float length);
    bool lenghtWallSphere(float length);
    void vecotrNon(IDColiCallArg& arg, const IDCmfPoliData* poli);
    void vecotrDef(IDColiCallArg& arg, const IDCmfPoliData* poli);
    void vecotrInst(IDColiCallArg& arg, const IDCmfPoliData* poli);
    // store a hit in the result: the nearest (stockNear), the nearest and the second one for negative lengths
    // (stockSecNear), the next table entry (stockTbl); then run the m_vecotr step on it
    void stockNear(IDColiCallArg& arg, const IDCmfPoliData* poli, float length);
    void stockSecNear(IDColiCallArg& arg, const IDCmfPoliData* poli, float length);
    void stockTbl(IDColiCallArg& arg, const IDCmfPoliData* poli, float length);
    void stockInstNear(IDColiCallArg& arg, const IDCmfPoliData* poli, float length);
    void stockInstSecNear(IDColiCallArg& arg, const IDCmfPoliData* poli, float length);
    void stockInstTbl(IDColiCallArg& arg, const IDCmfPoliData* poli, float length);

    wrkIDCmfWork* m_work;  // 0x0
    IDColiResult* m_result;  // 0x8
    const IDColiInput* m_input;  // 0x10
    // the instance being tested (inst*HitParts set it around the mesh test; IDColiGrandObj's constructor clears it);
    // the test* functions pick the stockInst*/vecotrInst steps while it is set
    const IDCmfPosData* m_instPosData;  // 0x18
    // the steps IDColiGrandObj's test* functions pick for the query kind
    bool (IDColiGrandMesh::*m_mesh)(unsigned int index);  // 0x20
    void (IDColiGrandMesh::*m_stock)(IDColiCallArg& arg, const IDCmfPoliData* poli, float length);  // 0x30
    void (IDColiGrandMesh::*m_stockInst)(IDColiCallArg& arg, const IDCmfPoliData* poli, float length);  // 0x40
    bool (IDColiGrandMesh::*m_lenght)(float length);  // 0x50
    // the second length test of capsules (testCapsule/testMoveCapsule set it)
    bool (IDColiGrandMesh::*m_lenghtSub)(float length);  // 0x60
    // the vector step IDColiGrandObj::testLine picks (vecotrNon, vecotrDef or vecotrInst) and the one for instances
    void (IDColiGrandMesh::*m_vecotr)(IDColiCallArg& arg, const IDCmfPoliData* poli);  // 0x70
    void (IDColiGrandMesh::*m_vecotrInst)(IDColiCallArg& arg, const IDCmfPoliData* poli);  // 0x80
};

class IDColiGrandTree : public IDColiGrandMesh {
public:
    // test a tree cell's entry: treeHitDef runs the mesh and instance tests, treeHitEnd stops at the first hit
    // (the parameter names are not the original's)
    bool treeHitDef(unsigned int index);
    bool treeHitEnd(unsigned int index);
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
    bool isLineAaBb(const float* max, const float* min);

    // the tree-entry test, the instance test and the box rejection the test* functions pick
    bool (IDColiGrandTree::*m_treeHit)(unsigned int index);  // 0x90
    bool (IDColiGrandTree::*m_instHit)(unsigned int index);  // 0xA0
    bool (IDColiGrandTree::*m_isAaBb)(const float* max, const float* min);  // 0xB0
};

}  // namespace idcoli

#endif
