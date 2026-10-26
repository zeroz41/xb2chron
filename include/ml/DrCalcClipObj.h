#ifndef ML_DRCALCCLIPOBJ_H
#define ML_DRCALCCLIPOBJ_H

namespace mm { class Vec3; }

namespace ml {
// a clip object of DrCalcClipMan's list (field names are not the original's)
class DrCalcClipObj {
public:
    bool testObjectClip(const mm::Vec3& pos, float radius, unsigned int* pBitTbl);
    // marked released in the frame stocked (DrMan::s_nDblStockIdx)
    void release();

    unsigned char pad_0[0x8];
    DrCalcClipObj* m_pNext;  // 0x8
    unsigned char pad_10[0x2C];
    unsigned int m_relFlag;  // 0x3C: release() sets 1 << DrMan::s_nDblStockIdx
};
}  // namespace ml

#endif
