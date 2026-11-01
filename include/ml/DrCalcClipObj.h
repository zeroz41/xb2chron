#ifndef ML_DRCALCCLIPOBJ_H
#define ML_DRCALCCLIPOBJ_H

namespace mm { class Vec3; }

namespace ml {
// a clip object of DrCalcClipMan's list (field names are not the original's)
class DrCalcClipObj {
public:
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
    bool clipcoli_box(const unsigned char* pData, const mm::Vec3& pos);
    bool clipcoli_sphere(const unsigned char* pData, const mm::Vec3& pos);
    bool clipcoli_cylinder(const unsigned char* pData, const mm::Vec3& pos);
    bool clipcoli_notrot_box(const unsigned char* pData, const mm::Vec3& pos);
    bool clipcoli_notrot_cylinder(const unsigned char* pData, const mm::Vec3& pos);
    // marked released in the frame stocked (DrMan::s_nDblStockIdx)
    void release();

    unsigned char pad_0[0x8];
    DrCalcClipObj* m_pNext;  // 0x8
    unsigned char pad_10[0x2C];
    unsigned int m_relFlag;  // 0x3C: release() sets 1 << DrMan::s_nDblStockIdx
};
}  // namespace ml

#endif
