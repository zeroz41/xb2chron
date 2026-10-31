#ifndef ML_DRRESMDOSEAMWRKPOSMPF_H
#define ML_DRRESMDOSEAMWRKPOSMPF_H

namespace ml {
// The mpf base positions of a seam map (DrMdoCtlMpf::setupMpf sets it up from the mpf data; DrMdoCtlMpfInst::
// calcSeamInstMpf reads it). Field and struct names are not the original's.
class DrResMdoSeamWrkPosMpf {
public:
    struct MpfHeader {
        unsigned char pad_0[0xC];
        unsigned int m_posOfs;   // 0xC
        unsigned char pad_10[0x4];
        unsigned int m_infoOfs;  // 0x14
        unsigned int m_posNum;   // 0x18
    };

    void setupMpfBasePos(const unsigned char* data);

    const unsigned char* m_pos;   // 0x0: data + m_posOfs
    const unsigned char* m_info;  // 0x8: data + m_infoOfs
    const unsigned char* m_data;  // 0x10
    unsigned int m_posNum;        // 0x18
    unsigned char pad_1C[0x4];
    void* m_work;                 // 0x20: cleared by setupMpfBasePos
    unsigned int m_workNum;       // 0x28: cleared by setupMpfBasePos
};
}  // namespace ml

#endif
