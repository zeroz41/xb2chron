#ifndef CLASSES_ML_DRCALCTEXSTMOBJ_H
#define CLASSES_ML_DRCALCTEXSTMOBJ_H

#include "ml/DrResMdoSeamMemMan.h"

namespace ml {
// table 0x7100B7EDC8
class DrCalcTexStmObj : public DrResChankList<DrCalcTexStmObj>::Node {
public:
    DrCalcTexStmObj() : m_pMem(), m_size(), m_flags(), pad_28() {}
    virtual ~DrCalcTexStmObj() {}  // slot 0

    // (field names are not the original's; DrCalcTexStreamMan::setupMem builds 0x30-byte objects and links them
    // into its DrResChankLists through the Node links at 0x08/0x10)
    void* m_pMem;  // 0x18: the memory the object hands out (DrCalcStmListObj::getAdder)
    int m_size;    // 0x20: setupMem gives the first object all of the manager's memory
    unsigned int m_flags;  // 0x24: DrCalcTexStreamMan::cntMemUpdate tests bit 1
    int pad_28;    // 0x28: zeroed by the constructor
    unsigned char pad_2C[0x4];
};
}  // namespace ml

#endif
