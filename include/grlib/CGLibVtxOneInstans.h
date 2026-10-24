#ifndef GRLIB_CGLIBVTXONEINSTANS_H
#define GRLIB_CGLIBVTXONEINSTANS_H

#include "grlib/CGLibMemHandle.h"

namespace grlib {
// one buffer of per-instance vertex data (CGLibVtxInstans without the frame halves). The field names are not the
// original's.
class CGLibVtxOneInstans {
public:
    CGLibVtxOneInstans();
    ~CGLibVtxOneInstans();
    void createInstansBuffer(int size);
    void beginInstansBuff();
    void updateInstansBuff();
    void* getBuff();

    unsigned int m_size;  // 0x0
    unsigned int m_offset;  // 0x4, the bytes written so far
    unsigned int m_flushed;  // 0x8, the bytes updateInstansBuff has written back
    unsigned char pad_C[0x4];
    unsigned long m_gpuAddress;  // 0x10
    CGLibMemType m_mem;  // 0x18
};
}  // namespace grlib

#endif
