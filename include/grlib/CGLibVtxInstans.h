#ifndef GRLIB_CGLIBVTXINSTANS_H
#define GRLIB_CGLIBVTXINSTANS_H

#include "grlib/CGLibMemHandle.h"

namespace grlib {

// the platform part of CGLibVtxInstans (its base, holding the ring's fields: which of them the original kept here
// is not known; getGPUAdress reads m_frameSize and m_gpuAddress)
class CGLibVtxInstans_plf {
public:
    // the GPU address of the current frame half (CGLibCtlVertex::setInstanceVertex)
    unsigned long getGPUAdress();

    unsigned int m_size;  // 0x0 (the names below are not the original's)
    unsigned int m_frameSize;  // 0x4, half of m_size: each frame half's part
    unsigned int m_offset;  // the bytes used so far: StreamObj::unlockStream advances it (the name is not the original's)
    unsigned int m_flushed;  // 0xC, the bytes updateInstansBuff has written back
    unsigned int m_base;  // 0x10, the current frame half's start
    unsigned char pad_14[0x4];
    CGLibMemType m_mem;  // 0x18
    unsigned long m_gpuAddress;  // 0x28
};

// a ring of per-instance vertex data: each user takes the next part of it (the name is the original's spelling)
class CGLibVtxInstans : public CGLibVtxInstans_plf {
public:
    CGLibVtxInstans();
    ~CGLibVtxInstans();
    // the frame's first instances go at the start again (ptlib's EffStateManager::begin)
    void beginInstansBuff();
    // where the next instances go
    void* getNextInstansBuff();
    // the instances written up to the offset handed to the GPU
    void updateInstansBuff();

    void createInstansBuffer(int size);
    void release();
};

}  // namespace grlib

#endif
