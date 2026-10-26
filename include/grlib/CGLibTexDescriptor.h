#ifndef GRLIB_CGLIBTEXDESCRIPTOR_H
#define GRLIB_CGLIBTEXDESCRIPTOR_H

#include "nvn/nvn.h"
#include "grlib/CGLibBuffFixAlloc.h"
#include "grlib/CGLibMemPool.h"

namespace grlib {
class CGLibTextureBuffer;

// the platform part of the texture descriptor pool: the NVN texture pool textures and images are registered in
// (the field names are not the original's)
class CGLibTexDescriptor_plf : public CGLibBuffFixAlloc {
public:
    ~CGLibTexDescriptor_plf();
    void bindTexture(const CGLibTextureBuffer& texture, int textureId, int imageId);
    // the pool slots of the texture's ids
    int setTexture(const CGLibTextureBuffer& texture);
    int setImage(const CGLibTextureBuffer& texture);

    CGLibMemPool m_pool;         // 0x28
    NVNtexturePool m_texPool;    // 0x48
};

class CGLibTexDescriptor : public CGLibTexDescriptor_plf {
public:
    CGLibTexDescriptor();
    ~CGLibTexDescriptor();
    void release();
    // initializes the texture pool on `pool` at `offset` with `num` descriptors; the bytes it takes
    unsigned int setup(CGLibMemPool& pool, unsigned int offset, unsigned int num);
    // sets the texture pool on the pipeline's command buffer
    void bind();
};
}  // namespace grlib

#endif
