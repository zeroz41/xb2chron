#ifndef CLASSES_GF_DATAOBJENEMYBLADE_H
#define CLASSES_GF_DATAOBJENEMYBLADE_H

#include "classes/gf/DataObjEnemy.h"

namespace gf {
// table 0x7100B4ED58
class DataObjEnemyBlade : public ::gf::DataObjEnemy {
public:
    virtual ~DataObjEnemyBlade();  // slot 0
    virtual void getModelResourceName() const;  // slot 4
    virtual void getMotionResourceName() const;  // slot 5
    virtual void getEffectResourceName() const;  // slot 6
    virtual void getName() const;  // slot 8
    virtual void getName(unsigned char*&, unsigned int&) const;  // slot 10
    virtual void getPArmor(bool) const;  // slot 23
    virtual void getEArmor(bool) const;  // slot 24
    virtual void getCriticalRate(bool) const;  // slot 25
    virtual void getGuardRate(bool) const;  // slot 26
    virtual void getWeaponDamage(bool) const;  // slot 29
    virtual void getWeaponStability(bool) const;  // slot 30
    virtual void getWeaponType(bool, int) const;  // slot 31
    virtual void getChestHeight() const;  // slot 32
    virtual void getLandingHeight() const;  // slot 33
    virtual void getIconData() const;  // slot 36
    virtual void getRace() const;  // slot 37
    virtual void getQuestRace() const;  // slot 38
    virtual void getGender() const;  // slot 39
    virtual void getAttribute(bool, int) const;  // slot 40
    virtual bool isDispInitExtraParts(unsigned int) const;  // slot 41
    virtual bool isEnbaleTarget() const { return false; }  // slot 54
    virtual void getEyeRotControl() const;  // slot 59
    virtual void getEquipWeapon(bool, int) const;  // slot 82
    virtual void getBladeArts(bool, unsigned int) const;  // slot 83
    virtual void getBladeArtsLevel(bool, unsigned int) const;  // slot 85
    virtual void getBladeArtsH(bool, unsigned int) const;  // slot 86
    virtual void getBladeArtsN(bool, unsigned int) const;  // slot 87
    virtual void getBladeArtsNH(bool, unsigned int) const;  // slot 88
    virtual void getBladeArtsEx(bool) const;  // slot 89
    virtual void getBladeArtsExH(bool) const;  // slot 90
    virtual void getBladeArtsEx2(bool) const;  // slot 91
    virtual void getBladeArtsEx2H(bool) const;  // slot 92
    virtual void getPersonality() const;  // slot 98
    virtual void getCoolTime() const;  // slot 99
};
}  // namespace gf

#endif
