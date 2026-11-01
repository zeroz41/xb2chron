#ifndef CLASSES_GF_DATAOBJENEMY_H
#define CLASSES_GF_DATAOBJENEMY_H

#include "classes/gf/IDataObj.h"
#include "gf/SDataEnemy.h"

namespace gf { class GF_OBJ_HANDLE; }

namespace gf {
// table 0x7100B4E918: an enemy's data, as its SDataEnemy holds it (the setup's, or its own one read by row id)
class DataObjEnemy : public ::gf::IDataObj {
public:
    DataObjEnemy(GF_OBJ_HANDLE* handle);
    DataObjEnemy(unsigned int id);
    virtual ~DataObjEnemy();  // slot 0
    virtual bool isValid() const;  // slot 3
    virtual const char* getModelResourceName() const;  // slot 4
    virtual const char* getMotionResourceName() const;  // slot 5
    virtual const char* getEffectResourceName() const;  // slot 6
    virtual const char* getName() const;  // slot 8
    virtual const char* getRotateBone() const;  // slot 9
    virtual bool getName(unsigned char*& bdat, unsigned int& id) const;  // slot 10
    virtual unsigned int getBdatId() const;  // slot 11
    virtual int getObjType() const { return 5; }  // slot 12
    virtual unsigned int getHp() const;  // slot 15
    virtual unsigned int getLevel(bool) const;  // slot 16
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
    virtual unsigned int getWeaponType(bool, int) const;  // slot 31
    virtual unsigned int getChestHeight() const;  // slot 32
    virtual unsigned int getFootStep() const;  // slot 34
    virtual unsigned int getFootStepEffect() const;  // slot 35
    virtual unsigned int getAttribute(bool, int) const;  // slot 40
    virtual bool isDispInitExtraParts(unsigned int) const;  // slot 41
    virtual bool vf42(unsigned int part) const;  // slot 42
    virtual const char* getVoiceStr() const;  // slot 45
    virtual bool isEnbaleTarget() const;  // slot 54
    virtual int getMenuOffset() const;  // slot 55
    virtual bool isNoCameraFade() const;  // slot 56
    virtual const char* getCamBone() const;  // slot 57
    virtual const char* getCenterBone() const;  // slot 58
    virtual unsigned int getEyeRotControl() const;  // slot 59
    virtual unsigned int getBlade(bool, int) const;  // slot 66
    virtual unsigned int getEquipWeapon(bool, int) const;  // slot 82
    virtual bool isWeaponDrawDisp() const;  // slot 110
    virtual unsigned int getBdatIdEnRsc() const;  // slot 111
    virtual unsigned int getBdatIdEnParam() const;  // slot 112
    virtual unsigned int getBdatIdEnArrange() const { return getBdatId(); }  // slot 113
    virtual bool isGuardFront() const;  // slot 114
    virtual bool isGuardLeft() const;  // slot 115
    virtual bool isGuardRight() const;  // slot 116
    virtual bool isGuardBack() const;  // slot 117
    virtual bool isFieldDamage() const;  // slot 118
    virtual unsigned int getResistancePower() const;  // slot 119
    virtual unsigned int getResistanceEther() const;  // slot 120
    virtual unsigned int getResistanceCombo() const;  // slot 121
    virtual unsigned int getInvincibleCombo() const;  // slot 122
    virtual unsigned int getLevelGold() const;  // slot 123
    virtual unsigned int getLevelExp() const;  // slot 124
    virtual unsigned int getLevelWp() const;  // slot 125
    virtual unsigned int getLevelSp() const;  // slot 126
    virtual unsigned int getGenus() const;  // slot 127
    virtual bool isLinkGenus() const;  // slot 128
    virtual float getLinkRadius() const;  // slot 129
    virtual unsigned int getGoldDivide() const;  // slot 130
    virtual unsigned int getGoldDivideRev() const;  // slot 131
    virtual const SDataEnemy* getSDataEnemy() const;  // slot 132

    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (1.0.0's stat getters call an unnamed
    // fn_710029100C). A member because its address lies among DataObjEnemy's functions and only its stat getters
    // call it. What it does: when the arrangement has an equipped blade (GfDataEnemy::getEquipBlade), adds the Param1
    // of its valid enhances (GfDataEnemy::getValidEnhance) of BTL_Enhance effect addEffect to value, then scales value
    // by the summed Param1 percents of effect rateEffect; false when there is no blade.
    static bool fn_7100229CEC(float& value, unsigned int arrange, unsigned int rateEffect, unsigned int addEffect);

    GF_OBJ_HANDLE* m_handle;  // the object's, -1 for data read by row id alone (the name is not the original's)
    SDataEnemy* m_sdata;  // the setup's, or m_sdataOwn (the name is not the original's)
    SDataEnemy m_sdataOwn;  // what DataObjEnemy(unsigned int) reads (the name is not the original's)
};
}  // namespace gf

#endif
