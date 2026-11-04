#ifndef CLASSES_GF_GFBDATCHRENARRANGE_H
#define CLASSES_GF_GFBDATCHRENARRANGE_H

#include "classes/gf/IDataBdat.h"
#include "classes/mm/mtl/PtrSingleton.h"

class CBdatWrapper;
namespace gf { class GfBdatChrEnArrange; }

namespace gf {
// table 0x7100B469E8; IDataBdat at 0x8 (GfDataBdat::initialize keeps it in its list)
class GfBdatChrEnArrange : public ::mm::mtl::PtrSingleton< ::gf::GfBdatChrEnArrange>, public ::gf::IDataBdat {
public:
    GfBdatChrEnArrange();
    virtual ~GfBdatChrEnArrange();  // slot 0
    virtual void bdatRefresh();  // slot 2
    void destroyFP();
    void createFP();
    unsigned int getChrEnArrangeStart() const;
    unsigned int getChrEnArrangeEnd() const;
    unsigned int getChrEnArrangeParamID(unsigned int id) const;  // the arrangement's GfBdatChrEnParam row
    unsigned int getChrEnArrangeEnemyBladeID(unsigned int id) const;
    unsigned int getChrEnArrangeBladeID(unsigned int id) const;
    unsigned int getChrEnArrangeBladeAtr(unsigned int id) const;
    unsigned int getChrEnArrangeExtraParts(unsigned int id) const;
    unsigned int getChrEnArrangeName(unsigned int id) const;
    unsigned int getChrEnArrangeLv(unsigned int id) const;
    unsigned int getChrEnArrangeLvRand(unsigned int id) const;
    unsigned int getChrEnArrangeHpOver(unsigned int id) const;
    unsigned int getChrEnArrangeExpRev(unsigned int id) const;
    unsigned int getChrEnArrangeGoldRev(unsigned int id) const;
    unsigned int getChrEnArrangeWPRev(unsigned int id) const;
    unsigned int getChrEnArrangeSPRev(unsigned int id) const;
    unsigned int getChrEnArrangeDropTableID(unsigned int id) const;
    unsigned int getChrEnArrangeDropTableID2(unsigned int id) const;
    unsigned int getChrEnArrangeDropTableID3(unsigned int id) const;
    unsigned int getChrEnArrangePreciousID(unsigned int id) const;
    // 2.0.0's symbols name it. What it does: row id's "Score" column (unsigned short) of CHR_EnArrange, 0 when the
    // handle is null or id is out of range (1.0.0 has no such column).
    unsigned int getChrEnArrangeScore(unsigned int id) const;
    // 2.0.0's symbols name it. What it does: row id's "ECube" column (unsigned short) of CHR_EnArrange, 0 when the
    // handle is null or id is out of range (1.0.0 has no such column).
    unsigned int getChrEnArrangeECube(unsigned int id) const;
    unsigned int getChrEnArrangeScale(unsigned int id) const;
    unsigned int getChrEnArrangeChrSize(unsigned int id) const;
    unsigned int getChrEnArrangeTurnSize(unsigned int id) const;
    bool isChrEnArrangeFlagNamed(unsigned int id) const;
    bool isChrEnArrangeFlagmBoss(unsigned int id) const;
    bool isChrEnArrangeFlagChild(unsigned int id) const;
    bool isChrEnArrangeFlagFAOff(unsigned int id) const;
    bool isChrEnArrangeFlagNoEcSkip(unsigned int id) const;
    bool isChrEnArrangeFlagLinkType(unsigned int id) const;
    bool isChrEnArrangeFlagChrColiOff(unsigned int id) const;
    bool isChrEnArrangeFlagNoTarget(unsigned int id) const;
    bool isChrEnArrangeFlagHikariSP4(unsigned int id) const;
    bool isChrEnArrangeFlagHomuri(unsigned int id) const;
    bool isChrEnArrangeFlagHikari(unsigned int id) const;
    bool isChrEnArrangeFlagFixed(unsigned int id) const;
    bool isChrEnArrangeFlagDropFront(unsigned int id) const;
    bool isChrEnArrangeFlagNoWarp(unsigned int id) const;
    bool isChrEnArrangeFlagIgnoreLevPow(unsigned int id) const;
    bool isChrEnArrangeFlagAlwaysAttack(unsigned int id) const;
    bool isChrEnArrangeFlagPGMax(unsigned int id) const;
    bool isChrEnArrangeFlagSalvage(unsigned int id) const;
    // 2.0.0's symbols name it. What it does: true when row id's "Serious" bit of the CHR_EnArrange "Flag" column is
    // set, false when either handle is null or id is out of range (1.0.0 has no such column).
    bool isChrEnArrangeFlagSerious(unsigned int id) const;
    // 2.0.0's symbols name it. What it does: true when row id's "NoChgBtl" bit of the CHR_EnArrange "Flag" column is
    // set, false when either handle is null or id is out of range (1.0.0 has no such column).
    bool isChrEnArrangeFlagNoChgBtl(unsigned int id) const;
    // 2.0.0's symbols name it. What it does: true when row id's "NoKasumi" bit of the CHR_EnArrange "Flag" column is
    // set, false when either handle is null or id is out of range (1.0.0 has no such column).
    bool isChrEnArrangeFlagNoKasumi(unsigned int id) const;
    unsigned int getChrEnArrangeLinkRadius(unsigned int id) const;
    unsigned int getChrEnArrangeDetects(unsigned int id) const;
    unsigned int getChrEnArrangeSearchRange(unsigned int id) const;
    unsigned int getChrEnArrangeSearchAngle(unsigned int id) const;
    unsigned int getChrEnArrangeSearchRadius(unsigned int id) const;
    unsigned int getChrEnArrangeBatInterval(unsigned int id) const;
    unsigned int getChrEnArrangeBatArea(unsigned int id) const;
    unsigned int getChrEnArrangeBatAreaType(unsigned int id) const;
    unsigned int getChrEnArrangeAiGroup(unsigned int id) const;
    unsigned int getChrEnArrangeAiGroupNum(unsigned int id) const;
    unsigned int getChrEnArrangeBookID(unsigned int id) const;
    unsigned int getChrEnArrangeEnhanceID1(unsigned int id) const;
    unsigned int getChrEnArrangeEnhanceID2(unsigned int id) const;
    unsigned int getChrEnArrangeEnhanceID3(unsigned int id) const;
    unsigned int getChrEnArrangeParamRev(unsigned int id) const;
    unsigned int getChrEnArrangeRstDebuffRev(unsigned int id) const;
    unsigned int getChrEnArrangeHealPotTypeRev(unsigned int id) const;
    unsigned int getChrEnArrangeSummonID(unsigned int id) const;
    unsigned int getChrEnArrangeBGMID(unsigned int id) const;
    unsigned int getChrEnArrangeSeEnvID(unsigned int id) const;
    unsigned int getChrEnArrangeZoneID(unsigned int id) const;
    unsigned int getChrEnArrangeDriverLev(unsigned int id) const;
    // 2.0.0's symbols name it. What it does: row id's "Race" column (unsigned short) of CHR_EnArrange, 0 when the
    // handle is null or id is out of range (1.0.0 has no such column).
    unsigned int getChrEnArrangeRace(unsigned int id) const;
    unsigned int getBTL_EnBookBaseEnemyID(unsigned int id) const;
    // 2.0.0's symbols name it. What it does: the BTL_NamedList table's first row id.
    unsigned int getBTL_NamedListStart() const;
    // 2.0.0's symbols name it. What it does: the BTL_NamedList table's first row id + row count (one past the last
    // row).
    unsigned int getBTL_NamedListEnd() const;
    // 2.0.0's symbols name it. What it does: row id's "EnemyID" column (unsigned short) of BTL_NamedList, 0 when the
    // handle is null or id is out of range (1.0.0 has no such column).
    unsigned int getBTL_NamedListEnemyID(unsigned int id) const;
    // 2.0.0's symbols name it. What it does: the BTL_NamedListIra table's first row id.
    unsigned int getBTL_NamedListIraStart() const;
    // 2.0.0's symbols name it. What it does: the BTL_NamedListIra table's first row id + row count (one past the last
    // row).
    unsigned int getBTL_NamedListIraEnd() const;
    // 2.0.0's symbols name it. What it does: row id's "EnemyID" column (unsigned short) of BTL_NamedListIra, 0 when the
    // handle is null or id is out of range (1.0.0 has no such column).
    unsigned int getBTL_NamedListIraEnemyID(unsigned int id) const;
    // the tables, by GfDataBdat id (s_aszGfBdatName), created in this order by createFP; m_fpChrEnArrange and
    // m_fpBTL_EnBook follow 1.0.0's accessors (getChrEnArrange.., getBTL_EnBook..), the two 3.0.1 tables' names are
    // their bdat names (not the original's)
    CBdatWrapper* m_fpChrEnArrange;  // 0x10, CHR_EnArrange
    CBdatWrapper* m_fpBTL_EnBook;  // 0x18, BTL_EnBook
    CBdatWrapper* m_fpBTL_NamedList;  // 0x20, BTL_NamedList
    CBdatWrapper* m_fpBTL_NamedListIra;  // 0x28, BTL_NamedListIra
};
}  // namespace gf

#endif
