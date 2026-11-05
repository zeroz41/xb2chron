#ifndef CLASSES_GMK_TUNK_B6D660_H
#define CLASSES_GMK_TUNK_B6D660_H

#include "classes/gmk/AGmkBase.h"
#include "plugin/Bdat.h"
#include "classes/gf/IGfObjListener.h"

namespace gmk {
// 2.0.0's symbols name it and its gimmick object type GmkCampGob (TGmkList's 5th argument, which has no table or symbol
// of its own): the gimmick of kind 0x3E (GmkSet::createGmkLists' list slot 0x3E, bdat column "campPop"). Its table is
// 0x7100B6D660 (installed by its list's Vector<T0>::resize in each element).
class GmkCampGob;

class GmkCamp : public ::gmk::AGmkBase {
public:
    GmkCamp() {}  // inline, user-provided: the defaults are stored by Vector<T>::resize/extend, no zero fill
    // the overrides its table holds (slot functions still carry their placeholder symbols, given per slot)
    virtual ~GmkCamp();  // slot 0 (~GmkCamp)
    virtual gmk::GmkType getGmkType() const;  // slot 2 (getGmkType)
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4 (create)
    virtual void dispose();  // slot 5 (dispose)
    virtual void update(float);  // slot 6 (update)
    virtual void debugDraw() const;  // slot 7 (debugDraw)
    virtual void onPlayerAccessed(gf::GF_OBJ_HANDLE*);  // slot 9 (onPlayerAccessed)
    // its bdat row (4 bytes: Vector<BdatInfo>::expand expand and initGmkBdatInfo initGmkBdatInfo match)
    class BdatInfo {
    public:
        // 2.0.0's symbols name it. What it does: true when the u16 at the row's offset 0 is 0, else
        // GfGameCond::isGameCond of it (a condition id).
        bool isCondMatched() const;
        // inline: initGmkBdatInfo (fn_710062C5C4) inlines it; the column names are the original's
        void create(CBdatWrapper bdat, int row, const AGmkBase& gmk) {
            m_condition = (unsigned short)Bdat::getValCheck(bdat.m_fp, "ConditionID", row, 2);
            m_campPointName = (unsigned short)Bdat::getValCheck(bdat.m_fp, "CampPointName", row, 2);
        }
        // 0x0: the condition isCondMatched tests, "ConditionID" (the name is not the original's)
        unsigned short m_condition;
        // 0x2: "CampPointName" (the name is not the original's; 4-byte stride in createGmk, zeroed by resize)
        unsigned short m_campPointName;
    };
    // 2.0.0's symbols name it. What it does: true when the local game flag 0xD869 + bdat id (type 1) is set;
    // onPlayerAccessed sets that flag. Caller gf::GfGmkLocator::getPosNum.
    bool isFound() const;
    const BdatInfo* getBdatInfo() const { return static_cast<const BdatInfo*>(m_createInfo.m_bdatInfo); }
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(0x3e);
    gf::GF_OBJ_HANDLE* m_gob = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);  // 0x48: dispose destroys it unless it is -1 (the name is not the original's)
    // fields: size from the stride 0x60: Vector<GmkCamp>::resize resize
    // 0x50: create squares the float of BDAT table 0x7B's member 0 at row 0x58; update keeps the game object only while
    // the interest point is that close (squared distance; the name is not the original's)
    float m_popDistSq = 0.0f;
    unsigned char pad_54[0x4];
    float pad_58 = 0.0f;  // create stores the float of BDAT table 0x7B's member 0 at row 0x5B
    // the data ends here (0x5C): Vector<T>::expand/extend copy pad_58 as 4 bytes; the rest is alignment
};
}  // namespace gmk

#endif
