#ifndef ML_MDSMATINFOHEADER_H
#define ML_MDSMATINFOHEADER_H

namespace ml {
// One material's header in a model resource (0x74 bytes: DrMdoMat::updateMatCallBack steps through an array of
// them). Only the fields DrMdoMat's material callbacks read are known; the field names are not the original's.
struct MdsMatInfoHeader {
    unsigned char pad_0[0xC];
    float m_color[4];  // 0x0C, scaled by DrMdoMat::matCall_CalcColor
    unsigned char pad_1C[0x24];
    unsigned int m_uniformOfs;  // 0x40, this material's first slot in MdoWrkMatRes::m_pUniformVal
    unsigned char pad_44[0x14];
    unsigned short m_callBackIdx;  // 0x58, first (callback, slot) pair of the material's list
    unsigned short m_callBackNum;  // 0x5A, number of pairs
    unsigned char pad_5C[0x8];
    unsigned short m_timeSlot;  // 0x64, uniform slot (from m_uniformOfs) of the time the *Time callbacks scale by
    unsigned char pad_66[0xE];
};
}  // namespace ml

#endif
