#ifndef ML_DRCALCCLIPMAN_H
#define ML_DRCALCCLIPMAN_H

namespace mm { class Vec3; }

namespace ml {
class DrCalcClipObj;
class DrCalcCpPlaneObj;
// The clip test manager. Only what DrCalcMan::begin and the clip tests use is declared so far (field names are not
// the original's).
class DrCalcClipMan {
public:
    void update();
    DrCalcClipObj* createClipObj(const void* resource);
    // whether any clip object clips the sphere (at pos, of radius)
    bool testObjectClip(const mm::Vec3& pos, float radius);
    // whether every clip plane object passes the sphere
    bool testPlaneClip(const mm::Vec3& pos, float radius);

    unsigned char pad_0[0x10];
    DrCalcClipObj* m_pClipObj;        // 0x10: the first clip object (createClipObj's)
    unsigned char pad_18[0x28];
    DrCalcCpPlaneObj* m_pCpPlaneObj;  // 0x40: the first clip plane object (createCpPlaneObj's)
    unsigned char pad_48[0x28];
    unsigned int* m_pBitTbl;          // 0x70: calcBitTbl's, passed to every DrCalcClipObj::testObjectClip
};
}  // namespace ml

#endif
