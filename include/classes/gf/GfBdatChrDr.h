#ifndef CLASSES_GF_GFBDATCHRDR_H
#define CLASSES_GF_GFBDATCHRDR_H

#include "classes/gf/IDataBdat.h"
#include "classes/mm/mtl/PtrSingleton.h"

class CBdatWrapper;
namespace gf { class GfBdatChrDr; }

namespace gf {
// table 0x7100B468F8; IDataBdat at 0x8 (GfDataBdat::initialize keeps it in its list)
class GfBdatChrDr : public ::mm::mtl::PtrSingleton< ::gf::GfBdatChrDr>, public ::gf::IDataBdat {
public:
    GfBdatChrDr();
    virtual ~GfBdatChrDr();  // slot 0
    virtual void bdatRefresh();  // slot 2
    void destroyFP();
    void createFP();
    unsigned int getChrDrStart() const;
    unsigned int getChrDrEnd() const;
    unsigned int getChrDrName(unsigned int id) const;
    unsigned int getChrDrRace(unsigned int id) const;
    unsigned int getChrDrRotateLimitPitch(unsigned int id) const;
    unsigned int getChrDrRotateLimitRoll(unsigned int id) const;
    unsigned int getChrDrGender(unsigned int id) const;
    const char* getChrDrModel(unsigned int id) const;
    unsigned int getChrDrCondition(unsigned int id) const;
    const char* getChrDrModel2(unsigned int id) const;
    const char* getChrDrMotion(unsigned int id) const;
    unsigned int getChrDrStill(unsigned int id) const;
    unsigned int getChrDrOffsetID(unsigned int id) const;
    unsigned int getChrDrEyeRot(unsigned int id) const;
    const char* getChrDrVoice(unsigned int id) const;
    const char* getChrDrCom_Eff(unsigned int id) const;
    unsigned int getChrDrAiID(unsigned int id) const;
    unsigned int getChrDrChestHeight(unsigned int id) const;
    unsigned int getChrDrLandingHeight(unsigned int id) const;
    unsigned int getChrDrFootStep(unsigned int id) const;
    unsigned int getChrDrFootStepEffect(unsigned int id) const;
    unsigned int getChrDrDefBlade1(unsigned int id) const;
    unsigned int getChrDrDefLvType(unsigned int id) const;
    unsigned int getChrDrDefLv(unsigned int id) const;
    unsigned int getChrDrDefWPType(unsigned int id) const;
    unsigned int getChrDrDefWP(unsigned int id) const;
    unsigned int getChrDrDefSPType(unsigned int id) const;
    unsigned int getChrDrDefSP(unsigned int id) const;
    unsigned int getChrDrDefAcce(unsigned int id) const;
    unsigned int getChrDrDefIdeaBlue(unsigned int id) const;
    unsigned int getChrDrDefIdeaRed(unsigned int id) const;
    unsigned int getChrDrDefIdeaWhite(unsigned int id) const;
    unsigned int getChrDrDefIdeaBlack(unsigned int id) const;
    unsigned int getChrDrHpMaxLv1(unsigned int id) const;
    unsigned int getChrDrStrengthLv1(unsigned int id) const;
    unsigned int getChrDrPowEtherLv1(unsigned int id) const;
    unsigned int getChrDrDexLv1(unsigned int id) const;
    unsigned int getChrDrAgilityLv1(unsigned int id) const;
    unsigned int getChrDrLuckLv1(unsigned int id) const;
    unsigned int getChrDrHpMaxLv99(unsigned int id) const;
    unsigned int getChrDrStrengthLv99(unsigned int id) const;
    unsigned int getChrDrPowEtherLv99(unsigned int id) const;
    unsigned int getChrDrDexLv99(unsigned int id) const;
    unsigned int getChrDrAgilityLv99(unsigned int id) const;
    unsigned int getChrDrLuckLv99(unsigned int id) const;
    unsigned int getChrDrCollisionId(unsigned int id) const;
    const char* getChrDrCenterBone(unsigned int id) const;
    const char* getChrDrCamBone(unsigned int id) const;
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it reads m_fpChrDr. What it does: returns row id's "IraParam" column of CHR_Dr (16 bits; 0 when the handle is null or id is out of range).
    unsigned int fn_71001F13E0(unsigned int id) const;
    unsigned int getChrDrWpnType(unsigned int id, unsigned int index) const;
    unsigned int getChrDrWpRate(unsigned int id, unsigned int index) const;
    unsigned int getChrDrDefBlade(unsigned int id, unsigned int slot) const;
    unsigned int getChrDrFavoriteCategory(unsigned int id, unsigned int slot) const;
    unsigned int getChrDrFavoriteItem(unsigned int id, unsigned int slot) const;
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it reads m_fpChrIr. What it does: returns CHR_Ir's first row id (Bdat::getIdTop), as getChrDrStart does for CHR_Dr.
    unsigned int fn_71001F15D4() const;
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it reads m_fpChrIr. What it does: returns CHR_Ir's first row id plus its row count (Bdat::getIdTop + getIdCount), as getChrDrEnd does for CHR_Dr.
    unsigned int fn_71001F15E0() const;
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it reads m_fpChrIr. What it does: returns row id's "driverID" column of CHR_Ir (16 bits; 0 when the handle is null or id is out of range).
    unsigned int fn_71001F161C(unsigned int id) const;
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it reads m_fpChrIr. What it does: returns row id's "Type" column of CHR_Ir (8 bits; 0 when the handle is null or id is out of range).
    unsigned int fn_71001F16A4(unsigned int id) const;
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it reads m_fpChrIr. What it does: returns row id's "GroupID" column of CHR_Ir (8 bits; 0 when the handle is null or id is out of range).
    unsigned int fn_71001F172C(unsigned int id) const;
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it reads m_fpChrIr. What it does: returns row id's "DefWpnAcce" column of CHR_Ir (16 bits; 0 when the handle is null or id is out of range).
    unsigned int fn_71001F17B4(unsigned int id) const;
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it reads m_fpChrIr. What it does: returns whether row id has the "WpnInNonView" bit of CHR_Ir's "Flag" column set (false when either handle is null or id is out of range).
    bool fn_71001F183C(unsigned int id) const;
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it reads m_fpChrIr. What it does: returns row id's "SeDriver" column of CHR_Ir (a string; null when the handle is null or id is out of range).
    const char* fn_71001F18D4(unsigned int id) const;
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it reads m_fpChrIr. What it does: returns row id's "SeBlade" column of CHR_Ir (a string; null when the handle is null or id is out of range).
    const char* fn_71001F1958(unsigned int id) const;
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it reads m_fpChrIr. What it does: returns row id's "KizunaReward1" column of CHR_Ir (16 bits; 0 when the handle is null or id is out of range).
    unsigned int fn_71001F19DC(unsigned int id) const;
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it reads m_fpChrIr. What it does: returns row id's "KizunaReward2" column of CHR_Ir (16 bits; 0 when the handle is null or id is out of range).
    unsigned int fn_71001F1A64(unsigned int id) const;
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it reads m_fpIraParty. What it does: returns row id's "Guest1" column of IRA_Party (8 bits; 0 when the handle is null or id is out of range).
    unsigned int fn_71001F1AEC(unsigned int id) const;
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it reads m_fpIraParty. What it does: returns row id's "Guest2" column of IRA_Party (8 bits; 0 when the handle is null or id is out of range).
    unsigned int fn_71001F1B74(unsigned int id) const;
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it reads m_fpIraParty. What it does: returns row id's value of the slot-th column of {"driver11", "driver21", "driver31"} (IRA_Party; slot table 0x7100B46980).
    unsigned int fn_71001F1BFC(unsigned int id, unsigned int slot) const;
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it reads m_fpIraParty. What it does: returns row id's value of the slot-th column of {"blade11", "blade21", "blade31"} (IRA_Party; slot table 0x7100B46998).
    unsigned int fn_71001F1C10(unsigned int id, unsigned int slot) const;
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it reads m_fpIraParty. What it does: returns row id's value of the slot-th column of {"blade12", "blade22", "blade32"} (IRA_Party; slot table 0x7100B469B0).
    unsigned int fn_71001F1C24(unsigned int id, unsigned int slot) const;
    CBdatWrapper* m_fpChrDr;  // 0x10, GfDataBdat table 0x88 (CHR_Dr)
    CBdatWrapper* m_fpChrIr;  // 0x18, GfDataBdat table 0x89 (CHR_Ir; new in 3.0.1, the name is not the original's)
    CBdatWrapper* m_fpIraParty;  // 0x20, GfDataBdat table 0x91 (IRA_Party; new in 3.0.1, the name is not the original's)
};
}  // namespace gf

#endif
