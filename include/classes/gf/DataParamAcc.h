#ifndef CLASSES_GF_DATAPARAMACC_H
#define CLASSES_GF_DATAPARAMACC_H

namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class SDataEnemy; }

namespace gf {
// table 0x7100B4C800
class DataParamAcc {
public:
    DataParamAcc(GF_OBJ_HANDLE* handle);
    virtual ~DataParamAcc();  // slot 0
    unsigned int getChestHeight() const;
    const SDataEnemy* getSDataEnemy() const;

    // fields: the object's IDataObj at 0x8 (setupObjHandle finds it; getChestHeight asks it); size 0x18, the
    // stack slot its users give it
    unsigned char pad_8[0x10];
};
}  // namespace gf

#endif
