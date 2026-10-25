#ifndef GRLIB_CGLIBONEUNIFORMBLOCK_H
#define GRLIB_CGLIBONEUNIFORMBLOCK_H

namespace grlib {
// a single-buffered uniform block (CGLibCtlVertex::setUniformVertex binds it as a vertex stream). Only the fields
// that function reads are known; their names are not the original's and the size is not known.
class CGLibOneUniformBlock {
public:
    unsigned char pad_0[0x8];
    int m_size;  // 0x8
    unsigned char pad_C[0x4];
    unsigned long m_gpuAddress;  // 0x10
};
}  // namespace grlib

#endif
