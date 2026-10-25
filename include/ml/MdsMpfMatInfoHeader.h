#ifndef ML_MDSMPFMATINFOHEADER_H
#define ML_MDSMPFMATINFOHEADER_H

namespace ml {
// A material's info header in an mpf resource; only the fields DrResMpfSampler reads are known. The field names
// are not the original's.
struct MdsMpfMatInfoHeader {
    unsigned char pad_0[0x16];
    // a sampler's flags (one per DrResMpfSampler sampler): bit 0/1 s/t clamp off, bit 2/3 s/t mirror, bit 4 point filter
    unsigned short m_samplerFlags0;  // 0x16
    unsigned char pad_18[0x2];
    unsigned short m_samplerFlags1;  // 0x1A
    unsigned char pad_1C[0x2];
    unsigned short m_samplerFlags2;  // 0x1E
};
}  // namespace ml

#endif
