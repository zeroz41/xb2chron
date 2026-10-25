#ifndef GRLIB_CGLIBVTLMEMPOOL_H
#define GRLIB_CGLIBVTLMEMPOOL_H

#include "nvn/nvn.h"

namespace grlib {
// a pool of GPU memory that vertex buffers take parts of (CGLibVtxVertex::createMemVertexBuff). setupBuffer
// shares the pool of a CGLibMemPoolAdder pool holding the buffer, else makes its own. The field names are not the
// original's.
class CGLibVtlMemPool {
public:
    CGLibVtlMemPool();
    ~CGLibVtlMemPool();
    void release();
    void setupBuffer(void* buffer, unsigned int size);
    // frees the pool once the GPU is done with it
    void delayRelease();
    NVNmemoryPool* m_pPool;        // 0x0: its own (a slot of the context's m_memPoolTbl) or the shared one
    unsigned long m_gpuAddress;    // 0x8, the GPU address of m_pMem
    unsigned int m_size;           // 0x10: 0 while there is no buffer
    unsigned long m_offset;        // 0x18: m_pMem's offset into the shared pool
    bool m_isOwner;                // 0x20: m_pPool is its own
    unsigned char* m_pMem;         // 0x28, the pool's memory
};
}  // namespace grlib

#endif
