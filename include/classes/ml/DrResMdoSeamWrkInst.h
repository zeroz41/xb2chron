#ifndef CLASSES_ML_DRRESMDOSEAMWRKINST_H
#define CLASSES_ML_DRRESMDOSEAMWRKINST_H

namespace ml {
// table 0x7100B7DB48
class DrResMdoSeamWrkInst {
public:
    // a model info (0x20 bytes); the name is not the original's
    struct MdlInfo {
        unsigned char pad_0[0x20];
    };
    virtual ~DrResMdoSeamWrkInst();  // slot 0
    void release();
    void beginMdl();
    // the next of the m_mdlNum model infos (0x20 bytes each), null after the last
    MdlInfo* getMdlInfo();
    unsigned char pad_8[0x144];
    int m_mdlNum;             // 0x14C (the name is not the original's)
    unsigned short m_mdlCnt;  // 0x150: beginMdl clears it (the name is not the original's)
    unsigned char pad_152[0x4E];
    MdlInfo* m_mdlInfo;       // 0x1A0 (the name is not the original's)
};
}  // namespace ml

#endif
