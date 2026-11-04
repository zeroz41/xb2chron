#ifndef CLASSES_GF_DATAOBJDRIVER_H
#define CLASSES_GF_DATAOBJDRIVER_H

#include "classes/gf/IDataObj.h"

namespace gf { enum FAVORITE : int; }
namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class SDataDriver; }
namespace gf { struct SDataIra; }

namespace gf {
// table 0x7100B4DC58
class DataObjDriver : public ::gf::IDataObj {
public:
    DataObjDriver(unsigned int id);
    DataObjDriver(GF_OBJ_HANDLE* handle);
    // 1.0.0 has it out of line (its name from its symbols); 3.0.1 inlines it and keeps no copy
    void setup(unsigned int id);
    void setupVirtualParam();
    virtual ~DataObjDriver();  // slot 0
    virtual void setMenuParam() { m_menuParam = true; }  // slot 2
    virtual bool isValid() const;  // slot 3
    virtual const char* getModelResourceName() const;  // slot 4
    virtual const char* getMotionResourceName() const;  // slot 5
    virtual const char* getEffectResourceName() const;  // slot 6
    virtual const char* getName() const;  // slot 8
    virtual bool getName(unsigned char*&, unsigned int&) const;  // slot 10
    virtual unsigned int getBdatId() const;  // slot 11
    virtual int getObjType() const { return 3; }  // slot 12
    virtual const SDataIdea* getIdea() const;  // slot 13
    virtual unsigned short getDataType() const;  // slot 14
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
    virtual unsigned int getGender() const;  // slot 39
    virtual unsigned int getAttribute(bool, int) const;  // slot 40
    virtual bool isScenarioMask() const;  // slot 43
    virtual unsigned int getRole() const;  // slot 44
    virtual const char* getVoiceStr() const;  // slot 45
    virtual void setVirtualLevel(unsigned int);  // slot 46
    virtual void setVirtualEquipWpn(unsigned int, int);  // slot 47
    virtual void setVirtualEquipAcc(unsigned int, unsigned int);  // slot 48
    virtual void setVirtualSetBlade(unsigned int, int);  // slot 49
    virtual void setVirtualEquipWpnAcce(unsigned int) override;  // slot 52
    virtual bool isVirtualSetting() const;  // slot 53
    virtual int getMenuOffset() const;  // slot 55
    virtual const char* getCamBone() const;  // slot 57
    virtual const char* getCenterBone() const;  // slot 58
    virtual unsigned int getEyeRotControl() const;  // slot 59
    virtual unsigned int getNorAtkDmgMin(bool) const;  // slot 60
    virtual unsigned int getNorAtkDmgMax(bool) const;  // slot 61
    virtual unsigned int getEquipAcce(unsigned int, bool) const;  // slot 62
    virtual unsigned int getEquipAcceResult(unsigned int, unsigned int, bool) const;  // slot 63
    virtual int getBladeSet(bool) const;  // slot 65
    virtual unsigned int getBlade(bool, int) const;  // slot 66
    virtual void setBladeSet(int);  // slot 67
    virtual unsigned int getExp() const;  // slot 68
    virtual unsigned int getBattleExp() const;  // slot 69
    virtual unsigned int getExpNext(bool) const;  // slot 70
    virtual unsigned int getBattleExpNext(bool) const;  // slot 71
    virtual unsigned int getWeaponPoint(unsigned int) const;  // slot 72
    virtual void addWeaponPoint(unsigned int, int);  // slot 73
    virtual unsigned int getSkillPoint() const;  // slot 74
    virtual void addSkillPoint(int);  // slot 75
    virtual unsigned int getDriverArts(unsigned int, unsigned int, unsigned int) const;  // slot 76
    virtual bool setDriverArts(unsigned int, int, unsigned int);  // slot 77
    virtual unsigned int getDriverArtsLevel(unsigned int) const;  // slot 78
    virtual void setDriverArtsLevel(unsigned int, unsigned int);  // slot 79
    virtual unsigned int getClass(bool) const;  // slot 80
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
    virtual unsigned int getFavoriteCategory(gf::FAVORITE) const;  // slot 100
    virtual unsigned int getFavoriteItem(gf::FAVORITE) const;  // slot 101

    unsigned int m_bdatId;  // the driver's row (getBdatId; the name is not the original's)
    SDataDriver* m_sdata;  // the driver's data (the name is not the original's)
    SDataIra* m_dlc;  // the DLC driver's record, none for others (the name is not the original's)
    GF_OBJ_HANDLE* m_handle;  // the object's, -1 for data read by row id alone (the name is not the original's)
    // a copy of the driver's data the virtual settings change; none without (setupVirtualParam allocates it,
    // isVirtualSetting tests it, the destructor deletes it; the name is not the original's)
    SDataDriver* m_virtual;
    SDataIra* m_virtualDlc;  // the same for a DLC driver's record (the name is not the original's)
    // the weapon each blade slot has under the virtual settings (setVirtualEquipWpn; the name is not the original's)
    unsigned int m_virtualWeapons[3];
    unsigned char pad_44[0x8];  // unknown; the constructors clear it
    bool m_menuParam;  // setMenuParam sets it (the name is not the original's)
};
}  // namespace gf

#endif
