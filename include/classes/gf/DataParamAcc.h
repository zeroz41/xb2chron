#ifndef CLASSES_GF_DATAPARAMACC_H
#define CLASSES_GF_DATAPARAMACC_H

namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class SDataEnemy; }

namespace gf {
// what kind of object a DataParamAcc reads (its constructor's third argument)
enum GimmickType {};

// table 0x7100B4C800; 0x18 bytes on GfMenuFieldSkillList::addFieldSkillFromBlade's stack
class DataParamAcc {
public:
    DataParamAcc(GF_OBJ_HANDLE* handle);
    DataParamAcc(unsigned int type, unsigned int id, GimmickType gimmick);
    virtual ~DataParamAcc();  // slot 0
    bool isValid() const;
    unsigned int getChestHeight() const;
    const SDataEnemy* getSDataEnemy() const;
    unsigned int getFieldSkill(unsigned int index, bool flag) const;
    unsigned char getFieldSkillLevel(unsigned int index, bool flag) const;

    // fields: the object's IDataObj at 0x8 (setupObjHandle finds it; getChestHeight asks it); size 0x18, the
    // stack slot its users give it
    unsigned char pad_8[0x10];
};
}  // namespace gf

#endif
