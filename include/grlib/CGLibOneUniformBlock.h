#ifndef GRLIB_CGLIBONEUNIFORMBLOCK_H
#define GRLIB_CGLIBONEUNIFORMBLOCK_H

namespace grlib {
// a single-buffered uniform block (CGLibCtlVertex::setUniformVertex binds it as a vertex stream). Only the fields
// that function and updateData read are known; their names are not the original's. LayerObjTopMemObj keeps two
// arrays of them 0x28 apart per element, so the size is 0x28.
class CGLibOneUniformBlock {
public:
    void updateData();

    void* m_buffer;  // 0x0: updateData flushes m_size bytes from it
    int m_size;  // 0x8
    unsigned char pad_C[0x4];
    unsigned long m_gpuAddress;  // 0x10
    unsigned char pad_18[0x10];
};
}  // namespace grlib

#endif
