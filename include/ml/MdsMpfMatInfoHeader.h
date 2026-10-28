#ifndef ML_MDSMPFMATINFOHEADER_H
#define ML_MDSMPFMATINFOHEADER_H

namespace ml {
// A material's info header in an mpf resource; only the fields DrResMpfSampler reads are known. The field names
// are not the original's.
struct MdsMpfMatInfoHeader {
    unsigned char pad_0[0x4];
    // 0x04: bit 8 selects the shader variant with a per-material uniform block (DrMdoShdSetMpf::mpfshd_drw_*)
    unsigned int m_flags;
    unsigned char pad_8[0xA];
    unsigned short m_matUniformIdx;  // 0x12: the MdoWrkMatRes::m_pMatUniformArray block mpfshd_drw_* bind
    unsigned short m_texIdx;         // 0x14: the MdoWrkMatRes::m_ppTexture entry mpfshd_drw_* bind
    // a sampler's flags (one per DrResMpfSampler sampler): bit 0/1 s/t clamp off, bit 2/3 s/t mirror, bit 4 point filter
    unsigned short m_samplerFlags0;  // 0x16
    unsigned char pad_18[0x2];
    unsigned short m_samplerFlags1;  // 0x1A
    unsigned char pad_1C[0x2];
    unsigned short m_samplerFlags2;  // 0x1E
};
}  // namespace ml

#endif
