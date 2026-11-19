#ifndef ML_DRIBLCOLIACC_H
#define ML_DRIBLCOLIACC_H

#include "mm/Vec3.h"
#include "mm/mtl/ReservedBitflag.h"
#include "ml/DrIBLObj.h"
#include "mtl/MemManager.h"

namespace ml {
// a node of the IBL collision box tree (layout from testTreeColi/testTreeInvalidColi; the field names are not the
// original's)
struct _EnvColiListTreeData {
    float max[3];              // 0x0: the box (x, y, z)
    float min[3];              // 0xC
    unsigned int childOfs;     // 0x18: resource offset of childNum u16 node indices
    unsigned int primOfs;      // 0x1C: resource offset of primNum u16 primitive indices
    unsigned short childNum;   // 0x20
    unsigned short primNum;    // 0x22
};
// a collision primitive of the IBL resource, 0x18 bytes (layout from testTreeColi; the field names are not the
// original's)
struct _IBLPrimHeader {
    unsigned int dataOfs;      // 0x0: resource offset of the shape data
    unsigned short type;       // 0x4: index into DrIBLColiAcc::s_pColiTest
    unsigned short bit;        // 0x6: index into DrIBLColiAcc::m_bits
    unsigned short priority;   // 0x8: testTreeColi keeps the hit with the highest
    unsigned char pad_a[0xE];
};

// the IBL collision tests (DrIBLMan::update calls testTreeInvalidColi). Like DrEnvColiObj's tests, but each shape
// carries its own axes: a box/cylinder is a 3x4 float matrix (axes in columns 0..2 of rows 0x0/0x10/0x20, centre at
// 0x30, bounding radius 0x3C) and half extents at 0x40..0x48; a sphere/unrotated shape has its centre at 0x0, radius
// 0xC and half extents at 0x10..0x18. Only what this unit's functions use is declared.
class DrIBLColiAcc {
public:
    void testTreeInvalidColi(const _EnvColiListTreeData* tree, const mm::Vec3& pos, float range);
    bool testTreeColi(const _EnvColiListTreeData* tree, const mm::Vec3& pos, float range, const _IBLPrimHeader*& hit);
    bool envcoli_box(const unsigned char* data, const mm::Vec3& pos, float range);
    bool envcoli_sphere(const unsigned char* data, const mm::Vec3& pos, float range);
    bool envcoli_cylinder(const unsigned char* data, const mm::Vec3& pos, float range);
    bool envcoli_notrot_box(const unsigned char* data, const mm::Vec3& pos, float range);
    bool envcoli_notrot_cylinder(const unsigned char* data, const mm::Vec3& pos, float range);

    // the test of each shape type (testTreeColi and testTreeInvalidColi call through it)
    static bool (DrIBLColiAcc::*s_pColiTest[5])(const unsigned char*, const mm::Vec3&, float);

    // inline (no symbol): DrIBLObj::initialize builds it over its resource
    DrIBLColiAcc(const void* res, mtl::ALLOC_HANDLE handle) {
        const DrIBLObj::ResHeader* header = static_cast<const DrIBLObj::ResHeader*>(res);
        const unsigned char* data = static_cast<const unsigned char*>(res);
        m_res = data;
        m_prims = reinterpret_cast<const _IBLPrimHeader*>(data + header->primOfs);
        if (header->treeNum != 0) {
            m_tree = reinterpret_cast<const _EnvColiListTreeData*>(data + header->treeOfs);
        }
        if (header->invalidTreeNum != 0) {
            m_invalidTree = reinterpret_cast<const _EnvColiListTreeData*>(data + header->invalidTreeOfs);
        }
        m_bits.initialize(mtl::MemManager::getAllocator(handle), header->num);
        m_bits.clrLocal();
    }
    // inline (no symbol): DrIBLObj's destructor deletes its accessor
    ~DrIBLColiAcc() { m_bits.destroy(); }

    // DrIBLObj::initialize allocates 0x40 bytes and fills these from the IBL resource; DrIBLMan::update passes
    // m_invalidTree/m_tree to testTreeInvalidColi/testTreeColi (the field names are not the original's)
    const unsigned char* m_res;  // 0x0: the resource the offsets count from
    const _IBLPrimHeader* m_prims;  // 0x8
    const _EnvColiListTreeData* m_tree;  // 0x10
    const _EnvColiListTreeData* m_invalidTree;  // 0x18
    unsigned short m_priority;  // 0x20: priority of testTreeColi's best hit
    unsigned char pad_22[0x6];
    mm::mtl::ReservedBitflag m_bits;  // 0x28, cleared by DrIBLMan::update before the tests
};
}  // namespace ml

#endif
