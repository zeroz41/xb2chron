#ifndef GRLIB_CGLIBVTXVERTEX_H
#define GRLIB_CGLIBVTXVERTEX_H

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

    unsigned char pad_0[0x28];
};

}  // namespace grlib

#endif
