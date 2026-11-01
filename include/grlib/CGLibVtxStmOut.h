#ifndef GRLIB_CGLIBVTXSTMOUT_H
#define GRLIB_CGLIBVTXSTMOUT_H

#include "grlib/CGLibMemHandle.h"

namespace grlib {
// a transform feedback (stream out) buffer: begin binds it (nvnCommandBufferBindTransformFeedbackBuffer with
// m_gpuAddress and m_size). The field names are not the original's.
class CGLibVtxStmOut {
public:
    CGLibVtxStmOut();
    ~CGLibVtxStmOut();
    void setStorageBuffer(unsigned int location);
    // binds `size` bytes from `offset` into the buffer (the parameter names are not the original's)
    void setStorageBuffer(unsigned int location, unsigned int offset, unsigned int size);
    void release();
    unsigned int getSize();
    // frees the buffer and allocates one of size bytes (rounded up to 4); nothing written yet
    void createWorkBuff(int size);
    // records into the buffer (the rasterizer off) until end; stride: what end's count is multiplied by (the
    // parameter names are not the original's)
    void begin(int stride);
    void end(unsigned int count);

    int m_used;    // 0x0: end's count times m_stride, the bytes written (createWorkBuff clears it)
    int m_size;    // 0x4, createWorkBuff's size rounded up to 4
    int m_stride;  // 0x8, begin stores its argument (createWorkBuff clears it)
    unsigned char pad_C[0x4];
    CGLibMemType m_mem;  // 0x10
    unsigned long m_gpuAddress;  // 0x20
};
}  // namespace grlib

#endif
