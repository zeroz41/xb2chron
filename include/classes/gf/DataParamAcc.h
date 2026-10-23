#ifndef CLASSES_GF_DATAPARAMACC_H
#define CLASSES_GF_DATAPARAMACC_H

namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class SDataEnemy; }

namespace gf {
// what kind of object a DataParamAcc reads (its constructor's third argument)
enum GimmickType : int {};  // 1: a treasure box (DataObjGmk reads its GfBdatRsc TboxList rows)

// table 0x7100B4C800; 0x18 bytes on GfMenuFieldSkillList::addFieldSkillFromBlade's stack
class DataParamAcc {
public:
    DataParamAcc(GF_OBJ_HANDLE* handle);
    DataParamAcc(unsigned int type, unsigned int id, GimmickType gimmick);
    virtual ~DataParamAcc();  // slot 0
    bool isValid() const;
    int getWeaponType(int index, bool flag) const;
    unsigned int getChestHeight() const;
    unsigned int getHp() const;
    unsigned int getHpMax(bool flag) const;
    const SDataEnemy* getSDataEnemy() const;
    unsigned int getFieldSkill(unsigned int index, bool flag) const;
    unsigned char getFieldSkillLevel(unsigned int index, bool flag) const;
    int getIconData() const;
    unsigned int getEquipWeapon(int index, bool flag) const;  // GfMenuWeaponAdapter asks (-1, false)
    unsigned int getLevel(bool flag) const;
    unsigned int getBladeArts(unsigned int index, bool flag) const;
    unsigned int getBladeArtsEnhance(unsigned int index, bool flag) const;
    unsigned int getBladeArtsLevel(unsigned int index, bool flag) const;
    unsigned int getBladeArtsH(unsigned int index, bool flag) const;
    unsigned int getBladeArtsN(unsigned int index, bool flag) const;
    unsigned int getBladeArtsNH(unsigned int index, bool flag) const;
    unsigned int getBladeArtsEx(bool flag) const;
    unsigned int getBladeArtsExH(bool flag) const;
    unsigned int getBladeArtsEx2(bool flag) const;
    unsigned int getBladeArtsEx2H(bool flag) const;
    unsigned int getBladeSkill(unsigned int index, bool flag) const;
    unsigned int getBladeSkillLevel(unsigned int index, bool flag) const;
    unsigned int getBlade(int index, bool flag) const;  // GfEvtModelDriver's constructor passes (-1, false)

    // fields: the object's IDataObj at 0x8 (setupObjHandle finds it; getChestHeight asks it); size 0x18, the
    // stack slot its users give it
    unsigned char pad_8[0x10];
};
}  // namespace gf

#endif
