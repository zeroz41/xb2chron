#ifndef CLASSES_ML_DRRESMDOSEAMWRKLOW_H
#define CLASSES_ML_DRRESMDOSEAMWRKLOW_H

namespace grlib { class CGLibVtxInstans; }

namespace ml {
// table 0x7100B7DB98
// The field names are not the original's.
class DrResMdoSeamWrkLow {
public:
    DrResMdoSeamWrkLow();
    virtual ~DrResMdoSeamWrkLow();  // slot 0
    void release();

    DrResMdoSeamWrkLow* m_prev;           // 0x08: list links, zeroed by the constructor
    DrResMdoSeamWrkLow* m_next;           // 0x10
    unsigned char pad_18[0x10];
    void* m_buf;                          // 0x28: deallocated by release
    // 0x30: the memory its stream reads into (callLowMdlStream); zeroed by the constructor and release (the name is
    // not the original's)
    DrResMdoSeamMemObj* m_memObj;
    unsigned char pad_38[0x8];
    grlib::CGLibVtxInstans* m_instans;    // 0x40: released and destroyed by release
    unsigned char pad_48[0x40];
    void* m_buf2;                         // 0x88: deallocated by release
    unsigned char pad_90[0xC];
    int m_num;                            // 0x9C: zeroed by the constructor and release
    int m_dataIdx;                        // 0xA0: its MapHead::m_lowMdlTblOfs entry (callLowMdlStream); zeroed by the constructor
    int pad_A4;
    int pad_A8;
    int pad_AC;
    int pad_B0;
    int pad_B4;
};
}  // namespace ml

#endif
