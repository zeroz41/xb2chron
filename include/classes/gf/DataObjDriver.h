#ifndef CLASSES_GF_DATAOBJDRIVER_H
#define CLASSES_GF_DATAOBJDRIVER_H

#include "classes/gf/IDataObj.h"

namespace gf { enum FAVORITE : int; }

namespace gf {
// table 0x7100B4DC58
class DataObjDriver : public ::gf::IDataObj {
public:
    virtual ~DataObjDriver();  // slot 0
    virtual void setMenuParam();  // slot 2
    virtual void isValid() const;  // slot 3
    virtual void getModelResourceName() const;  // slot 4
    virtual void getMotionResourceName() const;  // slot 5
    virtual void getEffectResourceName() const;  // slot 6
    virtual void getName() const;  // slot 8
    virtual void getName(unsigned char*&, unsigned int&) const;  // slot 10
    virtual void getBdatId() const;  // slot 11
    virtual void getObjType() const;  // slot 12
    virtual void getIdea() const;  // slot 13
    virtual void getDataType() const;  // slot 14
    virtual void getHp() const;  // slot 15
    virtual void getLevel(bool) const;  // slot 16
    virtual void getHpMax(bool) const;  // slot 17
    virtual void getStrength(bool) const;  // slot 18
    virtual void getPowerEther(bool) const;  // slot 19
    virtual void getDex(bool) const;  // slot 20
    virtual void getAgility(bool) const;  // slot 21
    virtual void getLuck(bool) const;  // slot 22
    virtual void getPArmor(bool) const;  // slot 23
    virtual void getEArmor(bool) const;  // slot 24
    virtual void getCriticalRate(bool) const;  // slot 25
    virtual void getGuardRate(bool) const;  // slot 26
    virtual void getAutoHate(bool) const;  // slot 27
    virtual void getArtsHate(bool) const;  // slot 28
    virtual void getWeaponDamage(bool) const;  // slot 29
    virtual void getWeaponStability(bool) const;  // slot 30
    virtual void getWeaponType(bool, int) const;  // slot 31
    virtual void getChestHeight() const;  // slot 32
    virtual void getLandingHeight() const;  // slot 33
    virtual void getFootStep() const;  // slot 34
    virtual void getFootStepEffect() const;  // slot 35
    virtual void getIconData() const;  // slot 36
    virtual void getRace() const;  // slot 37
    virtual void getGender() const;  // slot 39
    virtual void getAttribute(bool, int) const;  // slot 40
    virtual void vf42();  // slot 42
    virtual void isScenarioMask() const;  // slot 43
    virtual void getRole() const;  // slot 44
    virtual void getVoiceStr() const;  // slot 45
    virtual void vf46();  // slot 46
    virtual void setVirtualEquipWpn(unsigned int, int);  // slot 47
    virtual void setVirtualEquipAcc(unsigned int, unsigned int);  // slot 48
    virtual void vf49();  // slot 49
    virtual void setVirtualEquipWpnChip(unsigned int);  // slot 50
    virtual void setVirtualEquipOrb(unsigned int, unsigned int);  // slot 51
    virtual void vf52();  // slot 52
    virtual void isVirtualSetting() const;  // slot 53
    virtual void getMenuOffset() const;  // slot 55
    virtual void getCamBone() const;  // slot 57
    virtual void getCenterBone() const;  // slot 58
    virtual void getEyeRotControl() const;  // slot 59
    virtual void getNorAtkDmgMin(bool) const;  // slot 60
    virtual void getNorAtkDmgMax(bool) const;  // slot 61
    virtual void getEquipAcce(unsigned int, bool) const;  // slot 62
    virtual void getEquipAcceResult(unsigned int, unsigned int, bool) const;  // slot 63
    virtual void getBladeSet(bool) const;  // slot 65
    virtual void getBlade(bool, int) const;  // slot 66
    virtual void setBladeSet(int);  // slot 67
    virtual void getExp() const;  // slot 68
    virtual void getBattleExp() const;  // slot 69
    virtual void getExpNext(bool) const;  // slot 70
    virtual void getBattleExpNext(bool) const;  // slot 71
    virtual void getWeaponPoint(unsigned int) const;  // slot 72
    virtual void addWeaponPoint(unsigned int, int);  // slot 73
    virtual void getSkillPoint() const;  // slot 74
    virtual void addSkillPoint(int);  // slot 75
    virtual void getDriverArts(unsigned int, unsigned int) const;  // slot 76
    virtual void setDriverArts(unsigned int, int, unsigned int);  // slot 77
    virtual void getDriverArtsLevel(unsigned int) const;  // slot 78
    virtual void setDriverArtsLevel(unsigned int, unsigned int);  // slot 79
    virtual void getClass(bool) const;  // slot 80
    virtual void getEquipWeapon(bool, int) const;  // slot 82
    virtual void getBladeArts(bool, unsigned int) const;  // slot 83
    virtual void getBladeArtsEnhance(bool, unsigned int) const;  // slot 84
    virtual void getBladeArtsLevel(bool, unsigned int) const;  // slot 85
    virtual void getBladeArtsH(bool, unsigned int) const;  // slot 86
    virtual void getBladeArtsN(bool, unsigned int) const;  // slot 87
    virtual void getBladeArtsNH(bool, unsigned int) const;  // slot 88
    virtual void getBladeArtsEx(bool) const;  // slot 89
    virtual void getBladeArtsExH(bool) const;  // slot 90
    virtual void getBladeArtsEx2(bool) const;  // slot 91
    virtual void getBladeArtsEx2H(bool) const;  // slot 92
    virtual void getBladeSkill(bool, unsigned int) const;  // slot 93
    virtual void getBladeSkillLevel(bool, unsigned int) const;  // slot 94
    virtual void getFieldSkill(bool, unsigned int) const;  // slot 95
    virtual void getFieldSkillLevel(bool, unsigned int) const;  // slot 96
    virtual void getKeyLevel() const;  // slot 97
    virtual void getFavoriteCategory(gf::FAVORITE) const;  // slot 100
    virtual void getFavoriteItem(gf::FAVORITE) const;  // slot 101
};
}  // namespace gf

#endif
