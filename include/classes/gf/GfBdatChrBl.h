#ifndef CLASSES_GF_GFBDATCHRBL_H
#define CLASSES_GF_GFBDATCHRBL_H

#include "classes/gf/IDataBdat.h"
#include "classes/mm/mtl/PtrSingleton.h"

class CBdatWrapper;
namespace gf { class GfBdatChrBl; }

namespace gf {
// table 0x7100B46750; IDataBdat at 0x8 (GfDataBdat::initialize keeps it in its list)
class GfBdatChrBl : public ::mm::mtl::PtrSingleton< ::gf::GfBdatChrBl>, public ::gf::IDataBdat {
public:
    GfBdatChrBl();
    virtual ~GfBdatChrBl();  // slot 0
    virtual void bdatRefresh();  // slot 2
    void destroyFP();
    void createFP();
    unsigned int getChrBlStart() const;
    unsigned int getChrBlEnd() const;
    unsigned int getChrBlName(unsigned int id) const;
    const char* getChrBlDebugName(unsigned int id) const;
    unsigned int getChrBlRace(unsigned int id) const;
    unsigned int getChrBlRotateLimitPitch(unsigned int id) const;
    unsigned int getChrBlRotateLimitRoll(unsigned int id) const;
    unsigned int getChrBlGender(unsigned int id) const;
    unsigned int getChrBlQuestRace(unsigned int id) const;
    const char* getChrBlModel(unsigned int id) const;
    const char* getChrBlMotion(unsigned int id) const;
    const char* getChrBlAddMotion(unsigned int id) const;
    unsigned int getChrBlCondition(unsigned int id) const;
    const char* getChrBlModel2(unsigned int id) const;
    const char* getChrBlMotion2(unsigned int id) const;
    unsigned int getChrBlStill(unsigned int id) const;
    const char* getChrBlVoice(unsigned int id) const;
    const char* getChrBlSePack(unsigned int id) const;
    const char* getChrBlCom_Eff(unsigned int id) const;
    const char* getChrBlCom_Vo(unsigned int id) const;
    unsigned int getChrBlOffsetID(unsigned int id) const;
    unsigned int getChrBlEyeRot(unsigned int id) const;
    unsigned int getChrBlChestHeight(unsigned int id) const;
    unsigned int getChrBlLandingHeight(unsigned int id) const;
    unsigned int getChrBlFootStep(unsigned int id) const;
    unsigned int getChrBlFootStepEffect(unsigned int id) const;
    unsigned int getChrBlWeaponType(unsigned int id) const;
    unsigned int getChrBlScale(unsigned int id) const;
    unsigned int getChrBlWpnScale(unsigned int id) const;
    bool isChrBlFlagOnlyWpn(unsigned int id) const;
    // 2.0.0's symbols name it. What it does: returns whether row id has the "OnlyChBtl" bit of the ChrBl "Flag" column
    // set (false when either handle is null or id is out of range).
    bool isChrBlFlagOnlyChBtl(unsigned int id) const;
    // 2.0.0's symbols name it. What it does: returns whether row id has the "FreeEngage" bit of the ChrBl "Flag" column
    // set (false when either handle is null or id is out of range).
    bool isChrBlFlagFreeEngage(unsigned int id) const;
    // 2.0.0's symbols name it. What it does: returns whether row id has the "NoMapRev" bit of the ChrBl "Flag" column
    // set (false when either handle is null or id is out of range).
    bool isChrBlFlagNoMapRev(unsigned int id) const;
    unsigned int getChrBlPrivateWpnR(unsigned int id) const;
    unsigned int getChrBlPrivateWpnL(unsigned int id) const;
    unsigned int getChrBlPrivateWpnR_Driver(unsigned int id) const;
    unsigned int getChrBlPrivateWpnL_Driver(unsigned int id) const;
    unsigned int getChrBlOrbNum(unsigned int id) const;
    unsigned int getChrBlAtr(unsigned int id) const;
    unsigned int getChrBlPersonality(unsigned int id) const;
    unsigned int getChrBlCoolTime(unsigned int id) const;
    unsigned int getChrBlDefWeapon(unsigned int id) const;
    unsigned int getChrBlBartsEx(unsigned int id) const;
    unsigned int getChrBlBartsEx2(unsigned int id) const;
    unsigned int getChrBlPArmor(unsigned int id) const;
    unsigned int getChrBlEArmor(unsigned int id) const;
    unsigned int getChrBlHpMaxRev(unsigned int id) const;
    unsigned int getChrBlStrengthRev(unsigned int id) const;
    unsigned int getChrBlPowEtherRev(unsigned int id) const;
    unsigned int getChrBlDexRev(unsigned int id) const;
    unsigned int getChrBlAgilityRev(unsigned int id) const;
    unsigned int getChrBlLuckRev(unsigned int id) const;
    unsigned int getChrBlBKLSet(unsigned int id) const;
    unsigned int getChrBlKeyAchievement(unsigned int id) const;
    unsigned int getChrBlCreateEventID(unsigned int id) const;
    unsigned int getChrBlNormalTalk(unsigned int id) const;
    unsigned int getChrBlCollisionId(unsigned int id) const;
    unsigned int getChrBlBladeSize(unsigned int id) const;
    const char* getChrBlCenterBone(unsigned int id) const;
    const char* getChrBlCamBone(unsigned int id) const;
    unsigned int getChrBlMerceName(unsigned int id) const;
    unsigned int getChrBlReleaseLock(unsigned int id) const;
    unsigned int getChrBlMnuCastName(unsigned int id) const;
    unsigned int getChrBlMnuIlustName(unsigned int id) const;
    unsigned int getChrBlIdea(unsigned int id, unsigned int slot) const;
    unsigned int getChrBlBArts(unsigned int id, unsigned int slot) const;
    unsigned int getChrBlBSkill(unsigned int id, unsigned int slot) const;
    unsigned int getChrBlFSkill(unsigned int id, unsigned int slot) const;
    unsigned int getChrBlNArts(unsigned int id, unsigned int slot) const;
    unsigned int getChrBlNArtsRecastRev(unsigned int id, unsigned int slot) const;
    unsigned int getChrBlArtsAchievement(unsigned int id, unsigned int slot) const;
    unsigned int getChrBlSkillAchievement(unsigned int id, unsigned int slot) const;
    unsigned int getChrBlFskillAchievement(unsigned int id, unsigned int slot) const;
    unsigned int getChrBlFavoriteCategory(unsigned int id, unsigned int slot) const;
    unsigned int getChrBlFavoriteItem(unsigned int id, unsigned int slot) const;
    unsigned int getChrBlExtraParts(unsigned int id, unsigned int slot) const;
    const char* getChrBlMnuVoice(unsigned int id, unsigned int slot) const;
    CBdatWrapper* m_fpChrBl;  // 0x10, GfDataBdat table 0x8A (CHR_Bl)
};
}  // namespace gf

#endif
