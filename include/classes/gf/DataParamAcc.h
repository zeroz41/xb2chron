#ifndef CLASSES_GF_DATAPARAMACC_H
#define CLASSES_GF_DATAPARAMACC_H

namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class SDataEnemy; }
namespace gf { class IDataObj; }
namespace gf { struct ParamObj; }
namespace gf { struct SDataIdea; }

namespace gf {
// what kind of object a DataParamAcc reads (its constructor's third argument)
enum GimmickType : int {};  // 1: a treasure box (DataObjGmk reads its GfBdatRsc TboxList rows)

// table 0x7100B4C800; 0x18 bytes on GfMenuFieldSkillList::addFieldSkillFromBlade's stack. It builds the object's
// IDataObj in one of 128 slots of _gfdac::s_accbuf and forwards each accessor to it while it is valid.
class DataParamAcc {
public:
    DataParamAcc(const ParamObj& obj);
    DataParamAcc(GF_OBJ_HANDLE* handle);
    DataParamAcc(unsigned int type, unsigned int id, GimmickType gimmick);
    virtual ~DataParamAcc();  // slot 0
    void setupObjHandle(GF_OBJ_HANDLE* handle);
    void setupObjId(unsigned int type, unsigned int id, GimmickType gimmick);
    bool isValid() const;
    const char* getName() const;
    const char* getVoiceStr() const;
    // Placeholder names (fn_71002208A4, fn_7100221170, fn_7100221F88): new or changed in 3.0.1, nothing in 1.0.0's
    // place names them. Members because they sit among DataParamAcc's forwarders and read this->m_obj. What they do:
    // fn_71002208A4 forwards its three arguments to IDataObj slot 76 (1.0.0's two-argument getDriverArts; 3.0.1's
    // DataObjDriver override picks its arts table by the third), 0 for an invalid object; fn_7100221170 forwards a
    // part to slot 42 (new in 3.0.1; DataObjEnemy's override), true for an invalid object; fn_7100221F88 forwards an
    // item to slot 52 (new in 3.0.1; DataObjDriver's override asks GfDataItem::getItemType of it).
    unsigned int getObjType() const;
    const char* getModelResourceName() const;
    const char* getMotionResourceName() const;
    const char* getEffectResourceName() const;
    unsigned int getBdatId() const;  // the SCOM_ENBOOK_* creates store it (0 for an invalid object)
    unsigned int getHp() const;
    unsigned int getLevel(bool flag) const;
    unsigned int getExp() const;
    unsigned int getBattleExp() const;
    unsigned int getExpNext(bool flag) const;
    unsigned int getWeaponPoint(unsigned int index) const;
    void addWeaponPoint(unsigned int index, int value);
    unsigned int getSkillPoint() const;
    unsigned int fn_71002208A4(unsigned int index, unsigned int index2, unsigned int index3) const;  // placeholder: see the comment above the block
    bool setDriverArts(unsigned int index, int value, unsigned int index2);  // was fn_7100220918 by position; forwards IDataObj slot 77 (see NOTES)
    unsigned int getDriverArtsLevel(unsigned int index) const;
    void setDriverArtsLevel(unsigned int index, unsigned int index2);
    unsigned int getHpMax(bool flag) const;
    unsigned int getStrength(bool flag) const;
    unsigned int getPowerEther(bool flag) const;
    unsigned int getDex(bool flag) const;
    unsigned int getAgility(bool flag) const;
    unsigned int getLuck(bool flag) const;
    unsigned int getPArmor(bool flag) const;
    unsigned int getEArmor(bool flag) const;
    unsigned int getCriticalRate(bool flag) const;
    unsigned int getGuardRate(bool flag) const;
    unsigned int getAutoHate(bool flag) const;
    unsigned int getArtsHate(bool flag) const;
    unsigned int getWeaponDamage(bool flag) const;
    unsigned int getWeaponStability(bool flag) const;
    unsigned int getChestHeight() const;
    unsigned int getLandingHeight() const;
    int getIconData() const;
    unsigned int getQuestRace() const;
    unsigned int getGender() const;
    unsigned int getAttribute(int value, bool flag) const;
    bool isDispInitExtraParts(unsigned int index) const;
    bool fn_7100221170(unsigned int index) const;  // placeholder: see the comment above the block
    bool isScenarioMask() const;
    unsigned int getRole(bool flag) const;
    int getMenuOffset() const;
    unsigned int getFootStep() const;
    unsigned int getEyeRotControl() const;
    const char* getRotateBone() const;
    unsigned int getPersonality() const;
    unsigned int getCoolTime() const;
    unsigned int getNorAtkDmgMin(bool flag) const;
    unsigned int getNorAtkDmgMax(bool flag) const;
    unsigned int getEquipAcce(unsigned int index, bool flag) const;
    int getBladeSet(bool flag) const;
    void setBladeSet(int value);
    unsigned int getBlade(int value, bool flag) const;
    unsigned int getClass(bool flag) const;
    unsigned int getEquipWeapon(int value, bool flag) const;
    unsigned int getWeaponType(int value, bool flag) const;
    unsigned int getBladePower(bool flag) const;
    unsigned int getBladeArts(unsigned int index, bool flag) const;
    unsigned int getBladeArtsEnhance(unsigned int index, bool flag) const;
    unsigned int getBladeArtsLevel(unsigned int index, bool flag) const;
    unsigned int getBladeArtsN(unsigned int index, bool flag) const;
    unsigned int getBladeArtsNH(unsigned int index, bool flag) const;
    unsigned int getBladeSkill(unsigned int index, bool flag) const;
    unsigned int getBladeSkillLevel(unsigned int index, bool flag) const;
    unsigned int getFieldSkill(unsigned int index, bool flag) const;
    unsigned int getFieldSkillLevel(unsigned int index, bool flag) const;
    unsigned int getBladeArtsH(unsigned int index, bool flag) const;
    unsigned int getBladeArtsEx(bool flag) const;
    unsigned int getBladeArtsExH(bool flag) const;
    unsigned int getBladeArtsEx2(bool flag) const;
    unsigned int getBladeArtsEx2H(bool flag) const;
    void setVirtualEquipAcc(unsigned int index, unsigned int index2);  // was fn_7100221DFC by position; forwards IDataObj slot 48 (see NOTES)
    void setVirtualSetBlade(unsigned int index, int value);  // was fn_7100221E64 by position; forwards IDataObj slot 49 (see NOTES)
    void setVirtualEquipWpnChip(unsigned int index);
    void setVirtualEquipOrb(unsigned int index, unsigned int index2);
    void fn_7100221F88(unsigned int index);  // placeholder: see the comment above the block
    void setMenuParam();
    unsigned int getBdatIdEnParam() const;  // was isGuardFront by position; forwards IDataObj slot 112 (see NOTES)
    unsigned int getResistancePower() const;  // was getResistanceCombo by position; forwards IDataObj slot 119 (see NOTES)
    unsigned int getResistanceEther() const;  // was getInvincibleCombo by position; forwards IDataObj slot 120 (see NOTES)
    unsigned int getLevelGold() const;
    unsigned int getLevelExp() const;
    unsigned int getLevelWp() const;
    unsigned int getLevelSp() const;
    unsigned int getGenus() const;
    bool isLinkGenus() const;
    float getLinkRadius() const;
    unsigned int getGoldDivide() const;
    unsigned int getGoldDivideRev() const;
    const SDataEnemy* getSDataEnemy() const;
    void setVirtualLevel(unsigned int index);
    bool isEnbaleTarget() const;
    bool isNoCameraFade() const;
    bool isWeaponDrawDisp() const;
    const char* getCenterBone() const;
    const char* getCamBone() const;

    IDataObj* m_obj;  // 0x8: built in s_accbuf by setupObjHandle / setupObjId (the name is not the original's)
    GF_OBJ_HANDLE* m_handle;  // the object setupObjHandle was given (the name is not the original's)
};

// an object's ideas (DataParamAcc's IDataObj::getIdea), and whether it is a blade's (object type 4)
class DataIdeaAcc {
public:
    DataIdeaAcc(DataParamAcc& acc);
    DataIdeaAcc(SDataIdea& idea, bool isBlade);
    unsigned int getLevel(unsigned int idea) const;
    // adds to an idea's point through SDataIdea::setPoint; returns 0 (the return type is a guess from the code)
    unsigned int addPoint(unsigned int idea, unsigned int point);

    SDataIdea* m_idea;  // (the names are not the original's)
    bool m_isBlade;
};
}  // namespace gf

#endif
