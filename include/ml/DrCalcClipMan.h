#ifndef ML_DRCALCCLIPMAN_H
#define ML_DRCALCCLIPMAN_H

namespace mm { class Vec3; }

namespace ml {
class DrCalcClipObj;
class DrCalcCpPlaneObj;
class DrCalcViewWork;
class DrMan;
// The clip test manager. Only what DrCalcMan::begin and the clip tests use is declared so far (field names are not
// the original's).
class DrCalcClipMan {
public:
    // DrCalcMan's constructor builds it (inline: the symbols have no copy)
    DrCalcClipMan(DrMan* drMan, DrCalcViewWork* viewWork)
        : m_pDrMan(drMan), m_pViewWork(viewWork), m_pClipObj(), pad_18(), m_pCpPlaneObj(), pad_48(), m_pBitTbl(),
          pad_78() {}
    ~DrCalcClipMan() { release(); }
    void release();
    void update();
    DrCalcClipObj* createClipObj(const void* resource);
    // whether any clip object clips the sphere (at pos, of radius)
    bool testObjectClip(const mm::Vec3& pos, float radius);
    // whether every clip plane object passes the sphere
    bool testPlaneClip(const mm::Vec3& pos, float radius);

    DrMan* m_pDrMan;                  // 0x0
    DrCalcViewWork* m_pViewWork;      // 0x8
    DrCalcClipObj* m_pClipObj;        // 0x10: the first clip object (createClipObj's)
    unsigned char pad_18[0x28];
    DrCalcCpPlaneObj* m_pCpPlaneObj;  // 0x40: the first clip plane object (createCpPlaneObj's)
    unsigned char pad_48[0x28];
    unsigned int* m_pBitTbl;          // 0x70: calcBitTbl's, passed to every DrCalcClipObj::testObjectClip
    unsigned char pad_78[0x8];        // DrCalcMan's constructor allocates 0x80 bytes
};
}  // namespace ml

#endif
