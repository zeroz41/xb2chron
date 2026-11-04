#ifndef CLASSES_GF_GFBDATCHRENPARAM_H
#define CLASSES_GF_GFBDATCHRENPARAM_H

#include "classes/gf/IDataBdat.h"
#include "classes/mm/mtl/PtrSingleton.h"

class CBdatWrapper;
namespace gf { class GfBdatChrEnParam; }

namespace gf {
// table 0x7100B46A58; IDataBdat at 0x8 (GfDataBdat::initialize keeps it in its list)
class GfBdatChrEnParam : public ::mm::mtl::PtrSingleton< ::gf::GfBdatChrEnParam>, public ::gf::IDataBdat {
public:
    GfBdatChrEnParam();
    virtual ~GfBdatChrEnParam();  // slot 0
    virtual void bdatRefresh();  // slot 2
    void destroyFP();
    void createFP();
    unsigned int getChrEnParamResourceID(unsigned int id) const;  // the param's GfBdatRsc enemy row
    unsigned int getChrEnParamAiID(unsigned int id) const;
    unsigned int getChrEnParamEnemyRole(unsigned int id) const;
    unsigned int getChrEnParamWalkSpeed(unsigned int id) const;
    unsigned int getChrEnParamRunSpeed(unsigned int id) const;
    unsigned int getChrEnParamBtlSpeed(unsigned int id) const;
    unsigned int getChrEnParamHpDefault(unsigned int id) const;
    unsigned int getChrEnParamHpLimit(unsigned int id) const;
    unsigned int getChrEnParamScoutStartHp(unsigned int id) const;
    unsigned int getChrEnParamScoutEndHp(unsigned int id) const;
    unsigned int getChrEnParamHpMaxRev(unsigned int id) const;
    unsigned int getChrEnParamStrengthRev(unsigned int id) const;
    unsigned int getChrEnParamPowEtherRev(unsigned int id) const;
    unsigned int getChrEnParamDexRev(unsigned int id) const;
    unsigned int getChrEnParamAgilityRev(unsigned int id) const;
    unsigned int getChrEnParamLuckRev(unsigned int id) const;
    unsigned int getChrEnParamParmor(unsigned int id) const;
    unsigned int getChrEnParamEarmor(unsigned int id) const;
    int getChrEnParamRstPower(unsigned int id) const;
    int getChrEnParamRstEther(unsigned int id) const;
    unsigned int getChrEnParamAtr(unsigned int id) const;
    unsigned int getChrEnParamCriticalRate(unsigned int id) const;
    unsigned int getChrEnParamGuardRate(unsigned int id) const;
    bool isChrEnParamFlagGrdDirFront(unsigned int id) const;
    bool isChrEnParamFlagGrdDirLeft(unsigned int id) const;
    bool isChrEnParamFlagGrdDirRight(unsigned int id) const;
    bool isChrEnParamFlagGrdDirBack(unsigned int id) const;
    bool isChrEnParamFlagFldDmgType(unsigned int id) const;
    // 2.0.0's symbols name it. What it does: true when row id's "TrgRndLady" bit of the CHR_EnParam "Flag" column is
    // set, false when either handle is null or id is out of range (bdatRefresh looks the bit up after FldDmgType's;
    // 1.0.0 has no such column).
    bool isChrEnParamFlagTrgRndLady(unsigned int id) const;
    unsigned int getChrEnParamHealPotDrop(unsigned int id) const;
    unsigned int getChrEnParamRstFiCombo(unsigned int id) const;
    unsigned int getChrEnParamIvdFiCombo(unsigned int id) const;
    unsigned int getChrEnParamAura(unsigned int id) const;
    unsigned int getChrEnParamDyingHP(unsigned int id) const;
    unsigned int getChrEnParamWTNormal(unsigned int id) const;
    unsigned int getChrEnParamWTDying(unsigned int id) const;
    unsigned int getChrEnParamHate0Target(unsigned int id) const;
    unsigned int getChrEnParamDeathArts(unsigned int id) const;
    unsigned int getChrEnParamDeathArtsStop(unsigned int id) const;
    unsigned int getChrEnParamArtsNum(unsigned int id, unsigned int slot) const;
    unsigned int getChrEnParamTableEnd() const;
    unsigned int getChrEnParamTableHpMaxBase(unsigned int id) const;
    unsigned int getChrEnParamTableStrengthBase(unsigned int id) const;
    unsigned int getChrEnParamTablePowEtherBase(unsigned int id) const;
    unsigned int getChrEnParamTableDexBase(unsigned int id) const;
    unsigned int getChrEnParamTableAgilityBase(unsigned int id) const;
    unsigned int getChrEnParamTableLuckBase(unsigned int id) const;
    unsigned int getChrEnParamRevHpMaxRev(unsigned int id) const;
    unsigned int getChrEnParamRevStrengthRev(unsigned int id) const;
    unsigned int getChrEnParamRevPowEtherRev(unsigned int id) const;
    unsigned int getChrEnParamRevDexRev(unsigned int id) const;
    unsigned int getChrEnParamRevAgilityRev(unsigned int id) const;
    unsigned int getChrEnParamRevLuckRev(unsigned int id) const;
    // an enemy group's enemy (slot 0-11)
    unsigned int getEnemyGroupEnemyID(unsigned int id, unsigned int slot) const;
    // the tables, by GfDataBdat id (s_aszGfBdatName); names follow 1.0.0's accessors (getChrEnParam.., getChrEnParamTable..,
    // getChrEnParamRev.., getChrEnRstDebuffRev.., getEnemyGroup..).
    CBdatWrapper* m_fpChrEnParam;  // 0x10, CHR_EnParam
    CBdatWrapper* m_fpChrEnParamTable;  // 0x18, CHR_EnParamTable
    CBdatWrapper* m_fpChrEnParamRev;  // 0x20, CHR_EnParam_Rev
    CBdatWrapper* m_fpChrEnRstDebuffRev;  // 0x28, CHR_EnRstDebuff_Rev
    CBdatWrapper* m_fpEnemyGroup;  // 0x30, FLD_EnemyGroup
};
}  // namespace gf

#endif
