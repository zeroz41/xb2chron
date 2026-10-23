#ifndef CLASSES_GF_DATAOBJENEMYBLADE_H
#define CLASSES_GF_DATAOBJENEMYBLADE_H

#include "classes/gf/DataObjEnemy.h"

namespace gf { class GfObjSetupEnemy; }
namespace gf { class SDataBlade; }

namespace gf {
// table 0x7100B4ED58: an enemy's blade's data
class DataObjEnemyBlade : public ::gf::DataObjEnemy {
public:
    DataObjEnemyBlade(GF_OBJ_HANDLE* handle);
    virtual ~DataObjEnemyBlade();  // slot 0
    virtual const char* getModelResourceName() const;  // slot 4
    virtual const char* getMotionResourceName() const;  // slot 5
    virtual const char* getEffectResourceName() const;  // slot 6
    virtual const char* getName() const;  // slot 8
    virtual bool getName(unsigned char*& bdat, unsigned int& id) const;  // slot 10
    virtual unsigned int getPArmor(bool) const;  // slot 23
    virtual unsigned int getEArmor(bool) const;  // slot 24
    virtual unsigned int getCriticalRate(bool) const;  // slot 25
    virtual unsigned int getGuardRate(bool) const;  // slot 26
    virtual unsigned int getWeaponDamage(bool) const;  // slot 29
    virtual unsigned int getWeaponStability(bool) const;  // slot 30
    virtual unsigned int getWeaponType(bool, int) const;  // slot 31
    virtual unsigned int getChestHeight() const;  // slot 32
    virtual unsigned int getLandingHeight() const;  // slot 33
    virtual unsigned int getIconData() const;  // slot 36
    virtual unsigned int getRace() const;  // slot 37
    virtual unsigned int getQuestRace() const;  // slot 38
    virtual unsigned int getGender() const;  // slot 39
    virtual unsigned int getAttribute(bool, int) const;  // slot 40
    virtual bool isDispInitExtraParts(unsigned int) const;  // slot 41
    virtual bool isEnbaleTarget() const { return false; }  // slot 54
    virtual unsigned int getEyeRotControl() const;  // slot 59
    virtual unsigned int getEquipWeapon(bool, int) const;  // slot 82
    virtual unsigned int getBladeArts(bool, unsigned int) const;  // slot 83
    virtual unsigned int getBladeArtsLevel(bool, unsigned int) const;  // slot 85
    virtual unsigned int getBladeArtsH(bool, unsigned int) const;  // slot 86
    virtual unsigned int getBladeArtsN(bool, unsigned int) const;  // slot 87
    virtual unsigned int getBladeArtsNH(bool, unsigned int) const;  // slot 88
    virtual unsigned int getBladeArtsEx(bool) const;  // slot 89
    virtual unsigned int getBladeArtsExH(bool) const;  // slot 90
    virtual unsigned int getBladeArtsEx2(bool) const;  // slot 91
    virtual unsigned int getBladeArtsEx2H(bool) const;  // slot 92
    virtual unsigned int getPersonality() const;  // slot 98
    virtual unsigned int getCoolTime() const;  // slot 99

    GfObjSetupEnemy* m_setup;  // the enemy's setup, its blade's owner (the name is not the original's)
    SDataBlade* m_sdataBlade;  // the blade's GfDataBlade::getSDataBlade (the name is not the original's)
};
}  // namespace gf

#endif
