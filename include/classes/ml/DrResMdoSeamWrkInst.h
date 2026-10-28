#ifndef CLASSES_ML_DRRESMDOSEAMWRKINST_H
#define CLASSES_ML_DRRESMDOSEAMWRKINST_H

namespace ml {
// table 0x7100B7DB48
class DrResMdoSeamWrkInst {
public:
    virtual ~DrResMdoSeamWrkInst();  // slot 0
    void release();
    void beginMdl();
    unsigned char pad_8[0x148];
    unsigned short m_mdlCnt;  // 0x150: beginMdl clears it (the name is not the original's)
};
}  // namespace ml

#endif
