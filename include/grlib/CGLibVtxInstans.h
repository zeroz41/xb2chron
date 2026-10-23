#ifndef GRLIB_CGLIBVTXINSTANS_H
#define GRLIB_CGLIBVTXINSTANS_H

namespace grlib {

// a ring of per-instance vertex data: each user takes the next part of it (the name is the original's spelling)
class CGLibVtxInstans {
public:
    CGLibVtxInstans();
    ~CGLibVtxInstans();
    // the frame's first instances go at the start again (ptlib's EffStateManager::begin)
    void beginInstansBuff();
    // where the next instances go
    void* getNextInstansBuff();
    // the instances written up to the offset handed to the GPU
    void updateInstansBuff();

    unsigned char pad_0[0x8];
    unsigned int m_offset;  // the bytes used so far: StreamObj::unlockStream advances it (the name is not the original's)
};

}  // namespace grlib

#endif
