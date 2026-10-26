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
    void release();
    unsigned int getSize();

    unsigned int pad_0;  // 0x0, createWorkBuff clears it
    unsigned int m_size;  // 0x4, createWorkBuff's size rounded up to 4
    unsigned int pad_8;  // 0x8, begin stores its argument
    unsigned char pad_C[0x4];
    CGLibMemType m_mem;  // 0x10
    unsigned long m_gpuAddress;  // 0x20
};
}  // namespace grlib

#endif
