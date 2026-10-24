#ifndef GRLIB_CGLIBVTXVERTEX_H
#define GRLIB_CGLIBVTXVERTEX_H

#include "grlib/CGLibMemHandle.h"

namespace grlib { class CGLibVtlMemPool; }

namespace grlib {

// a vertex buffer in GPU memory: its size, its stride and the vertex count, the memory and its GPU address
class CGLibVtxVertex {
public:
    CGLibVtxVertex();
    ~CGLibVtxVertex();
    // frees the memory once the GPU is done with it
    void delayRelease();
    void createVertexBuff(unsigned int size, unsigned int stride);
    // a copy of size bytes of vertices of the stride
    void createCopyVertexBuff(const void* vertices, unsigned int size, unsigned int stride);
    void release();
    void lock(void** ppBuffer, unsigned int* pSize);
    void unlock();
    // unlocked, size bytes from offset written (the parameter names are not the original's)
    void unlock(unsigned int offset, unsigned int size);

    void createMemVertexBuff(CGLibVtlMemPool* pool, unsigned int offset, unsigned int size, unsigned int stride);
    void resetVertexBuff(CGLibVtlMemPool* pool, unsigned int offset);

    // the names are not the original's
    unsigned int m_size;  // 0x0
    unsigned int m_stride;  // 0x4
    unsigned int m_num;  // 0x8, m_size / m_stride
    unsigned char pad_C[0x4];
    CGLibMemType m_mem;  // 0x10
    unsigned long m_gpuAddress;  // 0x20
};

}  // namespace grlib

#endif
