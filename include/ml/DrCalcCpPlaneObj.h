#ifndef ML_DRCALCCPPLANEOBJ_H
#define ML_DRCALCCPPLANEOBJ_H

namespace mm { class Vec3; }

namespace ml {
// a clip plane object of DrCalcClipMan's list (field names are not the original's)
class DrCalcCpPlaneObj {
public:
    bool testClip(const mm::Vec3& pos, float radius);
    // marked released in the frame stocked (DrMan::s_nDblStockIdx), its plane index reset
    void release();

    unsigned char pad_0[0x8];
    DrCalcCpPlaneObj* m_pNext;  // 0x8
    unsigned char pad_10[0x28];
    int m_planeNum;             // 0x38: update counts the planes into it
    int m_planeIdx;             // 0x3C: an index update reads; release zeroes it
    unsigned int m_relFlag;     // 0x40: release() sets 1 << DrMan::s_nDblStockIdx
};
}  // namespace ml

#endif
