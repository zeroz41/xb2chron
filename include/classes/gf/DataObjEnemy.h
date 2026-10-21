#ifndef CLASSES_GF_DATAOBJENEMY_H
#define CLASSES_GF_DATAOBJENEMY_H

#include "classes/gf/IDataObj.h"

namespace gf {
// table 0x7100B4E918
class DataObjEnemy : public ::gf::IDataObj {
public:
    virtual ~DataObjEnemy();  // slot 0
    virtual bool isValid() const;  // slot 3
    virtual const char* getModelResourceName() const;  // slot 4
    virtual const char* getMotionResourceName() const;  // slot 5
    virtual const char* getEffectResourceName() const;  // slot 6
    virtual void getName() const;  // slot 8
    virtual void getRotateBone() const;  // slot 9
    virtual void getName(unsigned char*&, unsigned int&) const;  // slot 10
    virtual void getBdatId() const;  // slot 11
    virtual void getObjType() const;  // slot 12
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
    virtual void getWeaponType(bool, int) const;  // slot 31
    virtual void getChestHeight() const;  // slot 32
    virtual void getFootStep() const;  // slot 34
    virtual void getFootStepEffect() const;  // slot 35
    virtual void getAttribute(bool, int) const;  // slot 40
    virtual bool isDispInitExtraParts(unsigned int) const;  // slot 41
    virtual void vf42();  // slot 42
    virtual bool isScenarioMask() const;  // slot 43
    virtual void getVoiceStr() const;  // slot 45
    virtual void vf46();  // slot 46
    virtual void setVirtualEquipWpn(unsigned int, int);  // slot 47
    virtual void setVirtualEquipAcc(unsigned int, unsigned int);  // slot 48
    virtual void vf49();  // slot 49
    virtual void setVirtualEquipWpnChip(unsigned int);  // slot 50
    virtual void setVirtualEquipOrb(unsigned int, unsigned int);  // slot 51
    virtual void vf52();  // slot 52
    virtual bool isEnbaleTarget() const;  // slot 54
    virtual void getMenuOffset() const;  // slot 55
    virtual bool isNoCameraFade() const;  // slot 56
    virtual void getCamBone() const;  // slot 57
    virtual void getCenterBone() const;  // slot 58
    virtual void getEyeRotControl() const;  // slot 59
    virtual void getBlade(bool, int) const;  // slot 66
    virtual void getEquipWeapon(bool, int) const;  // slot 82
    virtual bool isWeaponDrawDisp() const;  // slot 110
    virtual void getBdatIdEnRsc() const;  // slot 111
    virtual void getBdatIdEnParam() const;  // slot 112
    virtual void getBdatIdEnArrange() const;  // slot 113
    virtual bool isGuardFront() const;  // slot 114
    virtual bool isGuardLeft() const;  // slot 115
    virtual bool isGuardRight() const;  // slot 116
    virtual bool isGuardBack() const;  // slot 117
    virtual bool isFieldDamage() const;  // slot 118
    virtual void getResistancePower() const;  // slot 119
    virtual void getResistanceEther() const;  // slot 120
    virtual void getResistanceCombo() const;  // slot 121
    virtual void getInvincibleCombo() const;  // slot 122
    virtual void getLevelGold() const;  // slot 123
    virtual void getLevelExp() const;  // slot 124
    virtual void getLevelWp() const;  // slot 125
    virtual void getLevelSp() const;  // slot 126
    virtual void getGenus() const;  // slot 127
    virtual bool isLinkGenus() const;  // slot 128
    virtual void getLinkRadius() const;  // slot 129
    virtual void getGoldDivide() const;  // slot 130
    virtual void getGoldDivideRev() const;  // slot 131
    virtual void getSDataEnemy() const;  // slot 132
};
}  // namespace gf

#endif
