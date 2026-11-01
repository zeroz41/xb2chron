#ifndef ML_DRCALCCLIPMAN_H
#define ML_DRCALCCLIPMAN_H

#include "ml/DrResMdoSeamMemMan.h"

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
        : m_pDrMan(drMan), m_pViewWork(viewWork), m_clipList(), m_clipStockLists(), m_cpPlaneList(), m_cpPlaneStockLists(), m_pBitTbl(), m_bitTblSize(), m_flags() {}
    ~DrCalcClipMan() { release(); }
    void release();
    void update();
    // (re)allocates m_pBitTbl for the largest bit count of m_clipList's objects
    void calcBitTbl();
    DrCalcClipObj* createClipObj(const void* resource);
    DrCalcCpPlaneObj* createCpPlaneObj(const void* resource);
    // whether any clip object clips the sphere (at pos, of radius)
    bool testObjectClip(const mm::Vec3& pos, float radius);
    // whether every clip plane object passes the sphere
    bool testPlaneClip(const mm::Vec3& pos, float radius);

    DrMan* m_pDrMan;                  // 0x0
    DrCalcViewWork* m_pViewWork;      // 0x8
    DrResChankList<DrCalcClipObj> m_clipList;  // 0x10: the clip objects tested
    // 0x20: by DrMan::s_nDblStockIdx, createClipObj's new ones (update moves [DrMan::s_nDblIdx] into m_clipList)
    DrResChankList<DrCalcClipObj> m_clipStockLists[2];
    DrResChankList<DrCalcCpPlaneObj> m_cpPlaneList;  // 0x40: the clip plane objects tested
    DrResChankList<DrCalcCpPlaneObj> m_cpPlaneStockLists[2];  // 0x50: createCpPlaneObj's, as m_clipStockLists
    unsigned int* m_pBitTbl;          // 0x70: calcBitTbl's, passed to every DrCalcClipObj::testObjectClip
    int m_bitTblSize;                 // 0x78: m_pBitTbl's size in bytes
    unsigned int m_flags;             // 0x7C: bit 0: calcBitTbl due (update); DrCalcMan's constructor allocates 0x80 bytes
};
}  // namespace ml

#endif
