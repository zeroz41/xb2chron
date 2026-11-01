#ifndef CLASSES_GF_IDATAOBJ_H
#define CLASSES_GF_IDATAOBJ_H

namespace gf { enum FAVORITE : int; }
#include "classes/gf/DataParamAcc.h"
namespace gf { class SDataEnemy; }
namespace gf { struct SDataIdea; }
namespace mm { namespace mtl { template <typename, unsigned long> class FixedArray; }}

namespace gf {
// table none (its derived classes'). An object's game data, read from its bdat rows by the row id getBdatId gives.
// Every default below is inline: the original emits them after the unit's own functions, in table order, and every
// derived class's table points at the same copies.
class IDataObj {
public:
    virtual ~IDataObj() {}  // slot 0
    virtual void setMenuParam() {}  // slot 2
    virtual bool isValid() const = 0;  // slot 3
    virtual const char* getModelResourceName() const { return nullptr; }  // slot 4
    virtual const char* getMotionResourceName() const { return nullptr; }  // slot 5
    virtual const char* getEffectResourceName() const { return nullptr; }  // slot 6
    virtual const char* getSeResourceName() const { return nullptr; }  // slot 7
    virtual const char* getName() const = 0;  // slot 8
    virtual const char* getRotateBone() const { return nullptr; }  // slot 9
    // the message table and row of the name
    virtual bool getName(unsigned char*& bdat, unsigned int& id) const { return false; }  // slot 10
    virtual unsigned int getBdatId() const = 0;  // slot 11
    virtual int getObjType() const = 0;  // slot 12
    virtual const SDataIdea* getIdea() const { return nullptr; }  // slot 13
    virtual unsigned short getDataType() const { return 0; }  // slot 14
    virtual unsigned int getHp() const { return 0; }  // slot 15
    virtual unsigned int getLevel(bool) const { return 0; }  // slot 16
    virtual unsigned int getHpMax(bool) const { return 0; }  // slot 17
    virtual unsigned int getStrength(bool) const { return 0; }  // slot 18
    virtual unsigned int getPowerEther(bool) const { return 0; }  // slot 19
    virtual unsigned int getDex(bool) const { return 0; }  // slot 20
    virtual unsigned int getAgility(bool) const { return 0; }  // slot 21
    virtual unsigned int getLuck(bool) const { return 0; }  // slot 22
    virtual unsigned int getPArmor(bool) const { return 0; }  // slot 23
    virtual unsigned int getEArmor(bool) const { return 0; }  // slot 24
    virtual unsigned int getCriticalRate(bool) const { return 0; }  // slot 25
    virtual unsigned int getGuardRate(bool) const { return 0; }  // slot 26
    virtual unsigned int getAutoHate(bool) const { return 0; }  // slot 27
    virtual unsigned int getArtsHate(bool) const { return 0; }  // slot 28
    virtual unsigned int getWeaponDamage(bool) const { return 0; }  // slot 29
    virtual unsigned int getWeaponStability(bool) const { return 0; }  // slot 30
    virtual unsigned int getWeaponType(bool, int) const { return 0; }  // slot 31
    virtual unsigned int getChestHeight() const { return 0; }  // slot 32
    virtual unsigned int getLandingHeight() const { return 0; }  // slot 33
    virtual unsigned int getFootStep() const { return 0; }  // slot 34
    virtual unsigned int getFootStepEffect() const { return 1; }  // slot 35
    virtual unsigned int getIconData() const { return 0; }  // slot 36
    virtual unsigned int getRace() const { return 0; }  // slot 37
    virtual unsigned int getQuestRace() const { return 1; }  // slot 38
    virtual unsigned int getGender() const { return 0; }  // slot 39
    virtual unsigned int getAttribute(bool, int) const { return 0; }  // slot 40
    virtual bool isDispInitExtraParts(unsigned int) const { return false; }  // slot 41
    // new in 3.0.1 (1.0.0's table has no slot here); nothing names it
    virtual bool fn_710022BD80(unsigned int) const { return false; }  // slot 42
    virtual bool isScenarioMask() const { return false; }  // slot 43
    virtual unsigned int getRole() const { return 1; }  // slot 44
    virtual const char* getVoiceStr() const { return nullptr; }  // slot 45
    // slots 46 to 51 are 1.0.0's 45 to 50, named by its symbols
    virtual void setVirtualLevel(unsigned int) {}  // slot 46
    virtual void setVirtualEquipWpn(unsigned int, int) {}  // slot 47
    virtual void setVirtualEquipAcc(unsigned int, unsigned int) {}  // slot 48
    virtual void setVirtualSetBlade(unsigned int, int) {}  // slot 49
    virtual void setVirtualEquipWpnChip(unsigned int) {}  // slot 50
    virtual void setVirtualEquipOrb(unsigned int, unsigned int) {}  // slot 51
    // new in 3.0.1 (1.0.0's table has no slot here); nothing names it
    // takes an item (DataObjDriver's override asks GfDataItem::getItemType of it; DataParamAcc's forwards one)
    virtual void fn_710022BDB8(unsigned int) {}  // slot 52
    virtual bool isVirtualSetting() const { return false; }  // slot 53
    virtual bool isEnbaleTarget() const { return true; }  // slot 54
    virtual int getMenuOffset() const { return 0; }  // slot 55
    virtual bool isNoCameraFade() const { return false; }  // slot 56
    virtual const char* getCamBone() const { return nullptr; }  // slot 57
    virtual const char* getCenterBone() const { return nullptr; }  // slot 58
    virtual unsigned int getEyeRotControl() const { return 0; }  // slot 59
    virtual unsigned int getNorAtkDmgMin(bool) const { return 0; }  // slot 60
    virtual unsigned int getNorAtkDmgMax(bool) const { return 0; }  // slot 61
    virtual unsigned int getEquipAcce(unsigned int, bool) const { return 0; }  // slot 62
    virtual unsigned int getEquipAcceResult(unsigned int, unsigned int, bool) const { return 5; }  // slot 63
    virtual bool getEquipOrb(mm::mtl::FixedArray<unsigned short, 3ul>&, bool) const { return false; }  // slot 64
    virtual int getBladeSet(bool) const { return -1; }  // slot 65
    virtual unsigned int getBlade(bool, int) const { return 0; }  // slot 66
    virtual void setBladeSet(int) {}  // slot 67
    virtual unsigned int getExp() const { return 0; }  // slot 68
    virtual unsigned int getBattleExp() const { return 0; }  // slot 69
    virtual unsigned int getExpNext(bool) const { return 0; }  // slot 70
    virtual unsigned int getBattleExpNext(bool) const { return 0; }  // slot 71
    virtual unsigned int getWeaponPoint(unsigned int) const { return 0; }  // slot 72
    virtual void addWeaponPoint(unsigned int, int) {}  // slot 73
    virtual unsigned int getSkillPoint() const { return 0; }  // slot 74
    virtual void addSkillPoint(int) {}  // slot 75
    // three arguments in 3.0.1 (1.0.0's has two): DataParamAcc's forwarder passes w1-w3 and DataObjDriver's override
    // picks its table by the third
    virtual unsigned int getDriverArts(unsigned int, unsigned int, unsigned int) const { return 0; }  // slot 76
    virtual bool setDriverArts(unsigned int, int, unsigned int) { return false; }  // slot 77
    virtual unsigned int getDriverArtsLevel(unsigned int) const { return 0; }  // slot 78
    virtual void setDriverArtsLevel(unsigned int, unsigned int) {}  // slot 79
    virtual unsigned int getClass(bool) const { return 0; }  // slot 80
    virtual unsigned int getBladePower(bool) const { return 0; }  // slot 81
    virtual unsigned int getEquipWeapon(bool, int) const { return 0; }  // slot 82
    virtual unsigned int getBladeArts(bool, unsigned int) const { return 0; }  // slot 83
    virtual unsigned int getBladeArtsEnhance(bool, unsigned int) const { return 0; }  // slot 84
    virtual unsigned int getBladeArtsLevel(bool, unsigned int) const { return 0; }  // slot 85
    virtual unsigned int getBladeArtsH(bool, unsigned int) const { return 100; }  // slot 86
    virtual unsigned int getBladeArtsN(bool, unsigned int) const { return 0; }  // slot 87
    virtual unsigned int getBladeArtsNH(bool, unsigned int) const { return 100; }  // slot 88
    virtual unsigned int getBladeArtsEx(bool) const { return 0; }  // slot 89
    virtual unsigned int getBladeArtsExH(bool) const { return 100; }  // slot 90
    virtual unsigned int getBladeArtsEx2(bool) const { return 0; }  // slot 91
    virtual unsigned int getBladeArtsEx2H(bool) const { return 100; }  // slot 92
    virtual unsigned int getBladeSkill(bool, unsigned int) const { return 0; }  // slot 93
    virtual unsigned int getBladeSkillLevel(bool, unsigned int) const { return 0; }  // slot 94
    virtual unsigned int getFieldSkill(bool, unsigned int) const { return 0; }  // slot 95
    virtual unsigned int getFieldSkillLevel(bool, unsigned int) const { return 0; }  // slot 96
    virtual unsigned int getKeyLevel() const { return 0; }  // slot 97
    virtual unsigned int getPersonality() const { return 0; }  // slot 98
    virtual unsigned int getCoolTime() const { return 0; }  // slot 99
    virtual unsigned int getFavoriteCategory(gf::FAVORITE) const { return 0; }  // slot 100
    virtual unsigned int getFavoriteItem(gf::FAVORITE) const { return 0; }  // slot 101
    virtual unsigned int getArtsAchievement(unsigned int) const { return 0; }  // slot 102
    virtual unsigned int getSkillAchievement(unsigned int) const { return 0; }  // slot 103
    virtual unsigned int getFieldSkillAchievement(unsigned int) const { return 0; }  // slot 104
    virtual unsigned int getKeyAchievement() const { return 0; }  // slot 105
    virtual unsigned int getLinkNum() const { return 500; }  // slot 106
    virtual unsigned int getDeadNum() const { return 500; }  // slot 107
    virtual unsigned int getAppStNum() const { return 500; }  // slot 108
    virtual unsigned int getAppEndNum() const { return 500; }  // slot 109
    virtual bool isWeaponDrawDisp() const { return false; }  // slot 110
    virtual unsigned int getBdatIdEnRsc() const { return 0; }  // slot 111
    virtual unsigned int getBdatIdEnParam() const { return 0; }  // slot 112
    virtual unsigned int getBdatIdEnArrange() const { return 0; }  // slot 113
    virtual bool isGuardFront() const { return false; }  // slot 114
    virtual bool isGuardLeft() const { return false; }  // slot 115
    virtual bool isGuardRight() const { return false; }  // slot 116
    virtual bool isGuardBack() const { return false; }  // slot 117
    virtual bool isFieldDamage() const { return true; }  // slot 118
    virtual unsigned int getResistancePower() const { return 0; }  // slot 119
    virtual unsigned int getResistanceEther() const { return 0; }  // slot 120
    virtual unsigned int getResistanceCombo() const { return 0; }  // slot 121
    virtual unsigned int getInvincibleCombo() const { return 0; }  // slot 122
    virtual unsigned int getLevelGold() const { return 0; }  // slot 123
    virtual unsigned int getLevelExp() const { return 0; }  // slot 124
    virtual unsigned int getLevelWp() const { return 0; }  // slot 125
    virtual unsigned int getLevelSp() const { return 0; }  // slot 126
    virtual unsigned int getGenus() const { return 0; }  // slot 127
    virtual bool isLinkGenus() const { return false; }  // slot 128
    virtual float getLinkRadius() const { return 0.0f; }  // slot 129
    virtual unsigned int getGoldDivide() const { return 0; }  // slot 130
    virtual unsigned int getGoldDivideRev() const { return 0; }  // slot 131
    virtual const SDataEnemy* getSDataEnemy() const { return nullptr; }  // slot 132
    virtual GimmickType getGimmickType() const { return static_cast<GimmickType>(0); }  // slot 133
};
}  // namespace gf

#endif
