#ifndef GRLIB_CGLIBVTLMEMPOOL_H
#define GRLIB_CGLIBVTLMEMPOOL_H

namespace grlib {
// a pool of GPU memory that vertex buffers take parts of (CGLibVtxVertex::createMemVertexBuff). Only the fields
// the vertex buffers read are known; their names are not the original's.
class CGLibVtlMemPool {
public:
    unsigned char pad_0[0x8];
    unsigned long m_gpuAddress;  // 0x8, the pool's GPU address
    unsigned char pad_10[0x18];
    unsigned char* m_pMem;  // 0x28, the pool's memory
};
}  // namespace grlib

#endif
