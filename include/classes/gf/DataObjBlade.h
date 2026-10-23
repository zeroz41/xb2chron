#ifndef CLASSES_GF_DATAOBJBLADE_H
#define CLASSES_GF_DATAOBJBLADE_H

#include "classes/gf/IDataObj.h"

namespace gf { enum FAVORITE : int; }
namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class SDataBlade; }
namespace mm { namespace mtl { template <typename, unsigned long> class FixedArray; }}

namespace gf {
// table 0x7100B4E098
class DataObjBlade : public ::gf::IDataObj {
public:
    DataObjBlade(unsigned int id);
    DataObjBlade(GF_OBJ_HANDLE* handle);
    // 1.0.0 has both out of line (names from its symbols); 3.0.1 inlines them and keeps no copy
    void setup(unsigned int id);
    void setupVirtualParam();
    virtual ~DataObjBlade();  // slot 0
    virtual void setMenuParam() { m_menuParam = true; }  // slot 2
    virtual bool isValid() const;  // slot 3
    virtual const char* getModelResourceName() const;  // slot 4
    virtual const char* getMotionResourceName() const;  // slot 5
    virtual const char* getEffectResourceName() const;  // slot 6
    virtual const char* getSeResourceName() const;  // slot 7
    virtual const char* getName() const;  // slot 8
    virtual bool getName(unsigned char*&, unsigned int&) const;  // slot 10
    virtual unsigned int getBdatId() const;  // slot 11
    virtual int getObjType() const { return 4; }  // slot 12
    virtual const SDataIdea* getIdea() const;  // slot 13
    virtual unsigned short getDataType() const;  // slot 14
    virtual unsigned int getHpMax(bool) const;  // slot 17
    virtual unsigned int getStrength(bool) const;  // slot 18
    virtual unsigned int getPowerEther(bool) const;  // slot 19
    virtual unsigned int getDex(bool) const;  // slot 20
    virtual unsigned int getAgility(bool) const;  // slot 21
    virtual unsigned int getLuck(bool) const;  // slot 22
    virtual unsigned int getPArmor(bool) const;  // slot 23
    virtual unsigned int getEArmor(bool) const;  // slot 24
    virtual unsigned int getCriticalRate(bool) const;  // slot 25
    virtual unsigned int getGuardRate(bool) const;  // slot 26
    virtual unsigned int getAutoHate(bool) const;  // slot 27
    virtual unsigned int getArtsHate(bool) const;  // slot 28
    virtual unsigned int getWeaponDamage(bool) const;  // slot 29
    virtual unsigned int getWeaponStability(bool) const;  // slot 30
    virtual unsigned int getWeaponType(bool, int) const;  // slot 31
    virtual unsigned int getChestHeight() const;  // slot 32
    virtual unsigned int getLandingHeight() const;  // slot 33
    virtual unsigned int getFootStep() const;  // slot 34
    virtual unsigned int getFootStepEffect() const;  // slot 35
    virtual unsigned int getIconData() const;  // slot 36
    virtual unsigned int getRace() const;  // slot 37
    virtual unsigned int getQuestRace() const;  // slot 38
    virtual unsigned int getGender() const;  // slot 39
    virtual unsigned int getAttribute(bool, int) const;  // slot 40
    virtual bool isDispInitExtraParts(unsigned int) const;  // slot 41
    virtual unsigned int getRole() const;  // slot 44
    virtual const char* getVoiceStr() const;  // slot 45
    virtual void setVirtualEquipWpn(unsigned int, int);  // slot 47
    virtual void setVirtualEquipWpnChip(unsigned int);  // slot 50
    virtual void setVirtualEquipOrb(unsigned int, unsigned int);  // slot 51
    virtual bool isVirtualSetting() const;  // slot 53
    virtual bool isEnbaleTarget() const;  // slot 54
    virtual int getMenuOffset() const;  // slot 55
    virtual const char* getCamBone() const;  // slot 57
    virtual const char* getCenterBone() const;  // slot 58
    virtual unsigned int getEyeRotControl() const;  // slot 59
    virtual unsigned int getNorAtkDmgMin(bool) const;  // slot 60
    virtual unsigned int getNorAtkDmgMax(bool) const;  // slot 61
    virtual bool getEquipOrb(mm::mtl::FixedArray<unsigned short, 3ul>&, bool) const;  // slot 64
    virtual int getBladeSet(bool) const;  // slot 65
    virtual unsigned int getBlade(bool, int) const;  // slot 66
    virtual unsigned int getBladePower(bool) const;  // slot 81
    virtual unsigned int getEquipWeapon(bool, int) const;  // slot 82
    virtual unsigned int getBladeArts(bool, unsigned int) const;  // slot 83
    virtual unsigned int getBladeArtsEnhance(bool, unsigned int) const;  // slot 84
    virtual unsigned int getBladeArtsLevel(bool, unsigned int) const;  // slot 85
    virtual unsigned int getBladeArtsH(bool, unsigned int) const;  // slot 86
    virtual unsigned int getBladeArtsN(bool, unsigned int) const;  // slot 87
    virtual unsigned int getBladeArtsNH(bool, unsigned int) const;  // slot 88
    virtual unsigned int getBladeArtsEx(bool) const;  // slot 89
    virtual unsigned int getBladeArtsExH(bool) const;  // slot 90
    virtual unsigned int getBladeArtsEx2(bool) const;  // slot 91
    virtual unsigned int getBladeArtsEx2H(bool) const;  // slot 92
    virtual unsigned int getBladeSkill(bool, unsigned int) const;  // slot 93
    virtual unsigned int getBladeSkillLevel(bool, unsigned int) const;  // slot 94
    virtual unsigned int getFieldSkill(bool, unsigned int) const;  // slot 95
    virtual unsigned int getFieldSkillLevel(bool, unsigned int) const;  // slot 96
    virtual unsigned int getKeyLevel() const;  // slot 97
    virtual unsigned int getPersonality() const;  // slot 98
    virtual unsigned int getCoolTime() const;  // slot 99
    virtual unsigned int getFavoriteCategory(gf::FAVORITE) const;  // slot 100
    virtual unsigned int getFavoriteItem(gf::FAVORITE) const;  // slot 101
    virtual unsigned int getArtsAchievement(unsigned int) const;  // slot 102
    virtual unsigned int getSkillAchievement(unsigned int) const;  // slot 103
    virtual unsigned int getFieldSkillAchievement(unsigned int) const;  // slot 104
    virtual unsigned int getKeyAchievement() const;  // slot 105
    virtual unsigned int getLinkNum() const;  // slot 106
    virtual unsigned int getDeadNum() const;  // slot 107
    virtual unsigned int getAppStNum() const;  // slot 108
    virtual unsigned int getAppEndNum() const;  // slot 109

    SDataBlade* m_sdata;  // GfDataBlade::getSDataBlade's for the blade (the name is not the original's)
    GF_OBJ_HANDLE* m_handle;  // the object's, -1 for data read by row id alone (the name is not the original's)
    // a copy of the blade's data the virtual settings change; none without (isVirtualSetting; the destructor
    // deletes it; the name is not the original's)
    SDataBlade* m_virtual;
    unsigned int m_bdatId;  // the blade's row (getBdatId; the name is not the original's)
    bool m_menuParam;  // setMenuParam sets it (the name is not the original's)
};
}  // namespace gf

#endif
