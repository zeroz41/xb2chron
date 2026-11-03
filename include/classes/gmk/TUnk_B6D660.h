#ifndef CLASSES_GMK_TUNK_B6D660_H
#define CLASSES_GMK_TUNK_B6D660_H

#include "classes/gmk/AGmkBase.h"
#include "plugin/Bdat.h"
#include "classes/gf/IGfObjListener.h"

namespace gmk {
// Placeholder name: the gimmick of kind 0x3E (GmkSet::createGmkLists' list slot 0x3E, bdat column "campPop"),
// new in 3.0.1; nothing in 1.0.0 names it. Named by its table 0x7100B6D660 (the table its list's Vector<T0>::resize
// installs in each element).
//
// TUnk_B6D660Gob: placeholder name for its gimmick object type (TGmkList's 5th argument). No Gob class in the
// binary has a table or symbol of its own (they appear only inside TGmkList's mangled names), so it is named after
// the element's table, following the original's <element>Gob pattern (GmkTbox / GmkTboxGob).
class TUnk_B6D660Gob;

class TUnk_B6D660 : public ::gmk::AGmkBase {
public:
    // the overrides its table holds (slot functions still carry their placeholder symbols, given per slot)
    virtual ~TUnk_B6D660();  // slot 0 (fn_71005C401C)
    virtual gmk::GmkType getGmkType() const;  // slot 2 (fn_71005C4118)
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4 (fn_71005B94D8)
    virtual void dispose();  // slot 5 (fn_71005B9564)
    virtual void update(float);  // slot 6 (fn_71005B95CC)
    virtual void debugDraw() const;  // slot 7 (fn_71005B98F0)
    virtual void onPlayerAccessed(gf::GF_OBJ_HANDLE*);  // slot 9 (fn_71005B9928)
    // its bdat row (4 bytes: Vector<BdatInfo>::expand fn_710062C6F4 and initGmkBdatInfo fn_710062C5C4 match)
    class BdatInfo {
    public:
        // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address
        // (0x71005B94AC) sits just before this class's create (fn_71005B94D8) in GmkElevator's unit and
        // LocatorGimmick::update calls it on a kind-0x3E gimmick's m_createInfo.m_bdatInfo, where its siblings call
        // their BdatInfo's isPopCondMatched. What it does: true when the u16 at the row's offset 0 is 0, else
        // GfGameCond::isGameCond of it (a condition id).
        bool fn_71005B94AC() const;
        // inline: initGmkBdatInfo (fn_710062C5C4) inlines it; the column names are the original's
        void create(CBdatWrapper bdat, int row, const AGmkBase& gmk) {
            m_condition = (unsigned short)Bdat::getValCheck(bdat.m_fp, "ConditionID", row, 2);
            m_campPointName = (unsigned short)Bdat::getValCheck(bdat.m_fp, "CampPointName", row, 2);
        }
        // 0x0: the condition fn_71005B94AC tests, "ConditionID" (the name is not the original's)
        unsigned short m_condition = 0;
        // 0x2: "CampPointName" (the name is not the original's; 4-byte stride in createGmk, zeroed by resize)
        unsigned short m_campPointName = 0;
    };
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address (0x71005B98FC)
    // sits between this class's debugDraw (0x71005B98F0) and onPlayerAccessed (0x71005B9928) and it reads this's
    // bdat id. What it does: true when the local game flag 0xD869 + bdat id (type 1) is set; onPlayerAccessed sets that
    // flag. Caller gf::GfGmkLocator::getPosNum.
    bool fn_71005B98FC() const;
    const BdatInfo* getBdatInfo() const { return static_cast<const BdatInfo*>(m_createInfo.m_bdatInfo); }
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(0x3e);
    gf::GF_OBJ_HANDLE* m_gob;  // 0x48: dispose destroys it unless it is -1 (the name is not the original's)
    // fields: size from the stride 0x60: Vector<TUnk_B6D660>::resize fn_710062C3CC
    // 0x50: create squares the float of BDAT table 0x7B's member 0 at row 0x58; update keeps the game object only while
    // the interest point is that close (squared distance; the name is not the original's)
    float m_popDistSq;
    unsigned char pad_54[0x4];
    float pad_58;  // create stores the float of BDAT table 0x7B's member 0 at row 0x5B
    unsigned char pad_5c[0x4];
};
}  // namespace gmk

#endif
