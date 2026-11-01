#ifndef ML_DRCALCCLIPOBJ_H
#define ML_DRCALCCLIPOBJ_H

#include "ml/DrResMdoSeamMemMan.h"
#include "mtl/MemManager.h"

namespace mm { class Vec3; }

namespace ml {
class DrMan;
// a node of a clip list's box tree (layout from DrCalcClipObj::seachTree; the field names are not the original's)
struct MdsClipListTreeData {
    float max[3];              // 0x0: the box (x, y, z)
    float min[3];              // 0xC
    unsigned int childOfs;     // 0x18: resource offset of childNum u16 node indices (DrCalcClipObj::m_pTree)
    unsigned int leafOfs;      // 0x1C: resource offset of leafNum u16 shape indices (DrCalcClipObj::m_pShapeData)
    unsigned short childNum;   // 0x20
    unsigned short leafNum;    // 0x22
};
// a clip object of DrCalcClipMan's lists, linked through its Node base (field names are not the original's)
class DrCalcClipObj : public DrResChankList<DrCalcClipObj>::Node {
public:
    // The clip list resource's header (layout from setupClip and testObjectClip; the names are not the original's)
    struct ResHeader {
        unsigned char pad_0[0xC];
        unsigned int shapeOfs;      // 0xC: m_pShapeData's
        unsigned char pad_10[0x2C];
        unsigned int treeOfs;       // 0x3C: m_pTree's
        int bitNum;                 // 0x40
        unsigned char pad_44[0x4];
        unsigned int checkDataOfs;  // 0x48: m_pCheckData's
        int bitDataNum;             // 0x4C: the entries at bitDataOfs (none: no bit data)
        unsigned int bitDataOfs;    // 0x50: m_pBitData's
        unsigned char pad_54[0x4];
        unsigned int checkTreeOfs;  // 0x58: the tree seachCheckTree walks (from the header)
        unsigned char pad_5C[0x4];
        unsigned int offTreeOfs;    // 0x60: the tree seachOffTree walks
    };
    // a bit's entry in the resource (m_pBitData; the names are not the original's)
    struct BitInfo {
        float range;           // 0x0: seachCheckTree tests the bit only for a radius up to it
        unsigned short flags;  // 0x4: bit 0 set: a hit on this bit does not clip; bit 1: seachCheckTree skips it;
                               // bits 3/2 set m_relFlag 4/8
        short priority;        // 0x6: seachCheckTree keeps only the hits of the highest
    };
    // a clip shape's entry (m_pShapeData; the names are not the original's)
    struct ShapeEntry {
        unsigned int dataOfs;  // 0x0: resource offset of the shape data s_pColiCheck[type] tests
        unsigned short bit;    // 0x4: the bit a hit sets in m_pBitTbl
        short type;            // 0x6: index into s_pColiCheck
    };
    // a clip shape's display check (m_pCheckData; the names are not the original's)
    struct CheckEntry {
        unsigned short pad_0;
        unsigned short dispBit;  // 0x2: nonzero: the shape is skipped while DrMan's m_dispOffBits has this bit
    };
    // the shape tests by ShapeEntry::type (clipcoli_box, _sphere, _cylinder, _notrot_box, _notrot_cylinder)
    static bool (DrCalcClipObj::*s_pColiCheck[5])(const unsigned char* pData, const mm::Vec3& pos);

    // DrCalcClipMan::createClipObj's (inline: the symbols have no copy)
    DrCalcClipObj(const unsigned char* pRes, DrMan* drMan)
        : m_pBitData(), m_relFlag(), m_bitWorkSize(), m_hitPriority(), m_hitNum(), m_pBitWork(), m_pBitTbl() {
        setupClip(pRes, drMan);
    }
    // DrCalcClipMan::release's delete frees the bit work first (inline: the symbols have no copy)
    ~DrCalcClipObj() {
        if (m_pBitWork != nullptr) {
            mtl::MemManager::deallocate(m_pBitWork, 0, false);
        }
    }
    // A clip shape's resource data as the clipcoli_* tests read it (layout from those tests; the names are not the
    // original's): a bounding sphere (centre, squared radius) and the half sizes of the shape.
    struct ShapeData {
        float pos[3];     // 0x0
        float radiusSq;   // 0xC: the bounding sphere's; the cylinder's squared radius for clipcoli_notrot_cylinder
        float size[3];    // 0x10: half sizes (x, y, z); the cylinder's half height is size[0]
    };
    // a rotated shape: its axes (columns of the 3x4 matrix) before the shape data
    struct RotShapeData {
        float mtx[3][4];  // 0x0
        float pos[3];     // 0x30
        float radiusSq;   // 0x3C
        float size[3];    // 0x40: half sizes (x, y, z); the cylinder keeps its squared radius in size[0], its half
                          // height in size[1]
    };

    bool testObjectClip(const mm::Vec3& pos, float radius, unsigned int* pBitTbl);
    // takes the clip list resource; DrMan's allocator gives the bit work
    void setupClip(const unsigned char* pRes, DrMan* drMan);
    void seachTree(const MdsClipListTreeData* pTree, const mm::Vec3& pos);
    void seachCheckTree(const MdsClipListTreeData* pTree, const mm::Vec3& pos, float radius);
    void seachOffTree(const MdsClipListTreeData* pTree, const mm::Vec3& pos, float radius);
    // the data at ofs in the resource (inline: the names are not the original's)
    const unsigned char* getResData(unsigned int ofs) const {
        return reinterpret_cast<const unsigned char*>(m_pRes) + ofs;
    }
    const MdsClipListTreeData* getTree(unsigned int ofs) const {
        return reinterpret_cast<const MdsClipListTreeData*>(getResData(ofs));
    }
    bool clipcoli_box(const unsigned char* pData, const mm::Vec3& pos);
    bool clipcoli_sphere(const unsigned char* pData, const mm::Vec3& pos);
    bool clipcoli_cylinder(const unsigned char* pData, const mm::Vec3& pos);
    bool clipcoli_notrot_box(const unsigned char* pData, const mm::Vec3& pos);
    bool clipcoli_notrot_cylinder(const unsigned char* pData, const mm::Vec3& pos);
    // marked released in the frame stocked (DrMan::s_nDblStockIdx)
    void release();

    const ResHeader* m_pRes;  // 0x10: setupClip's resource
    const ShapeEntry* m_pShapeData;  // 0x18: setupClip's (the resource + shapeOfs)
    const MdsClipListTreeData* m_pTree;  // 0x20: setupClip's; DrCalcClipMan::update searches it (seachTree)
    const BitInfo* m_pBitData;  // 0x28: setupClip points it into the resource (nullptr when it has no bits)
    const CheckEntry* m_pCheckData;  // 0x30: setupClip's (the resource + checkDataOfs)
    int m_bitNum;            // 0x38: setupClip's; DrCalcClipMan::calcBitTbl sizes its table by the largest
    unsigned int m_relFlag;  // 0x3C: release() sets 1 << DrMan::s_nDblStockIdx
    short m_bitWorkSize;     // 0x40: setupClip's, the size of m_pBitWork
    short m_hitPriority;     // 0x42: the priority of m_hits (testObjectClip resets it to -1)
    short m_hitNum;          // 0x44: the bits in m_hits (testObjectClip resets it)
    unsigned short m_hits[9];  // 0x46: bits seachCheckTree hit (at most 8)
    unsigned int* m_pBitWork;  // 0x58: setupClip allocates it (m_bitWorkSize bytes); the destructor frees it
    unsigned int* m_pBitTbl; // 0x60: DrCalcClipMan::update stores its m_pBitTbl
};
}  // namespace ml

#endif
