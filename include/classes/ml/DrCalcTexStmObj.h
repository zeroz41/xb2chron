#ifndef CLASSES_ML_DRCALCTEXSTMOBJ_H
#define CLASSES_ML_DRCALCTEXSTMOBJ_H

namespace ml {
// table 0x7100B7EDC8
class DrCalcTexStmObj {
public:
    virtual ~DrCalcTexStmObj() {}  // slot 0

    // (field names are not the original's; DrCalcTexStreamMan::setupMem builds 0x30-byte objects, the links at 0x8
    // and 0x10 for its DrResChankList)
    unsigned char pad_8[0x10];
    void* m_pMem;  // 0x18: the memory the object hands out (DrCalcStmListObj::getAdder)
    unsigned char pad_20[0x10];
};
}  // namespace ml

#endif
