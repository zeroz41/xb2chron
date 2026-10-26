#ifndef GRLIB_CGLIBSAMPLERDESCRIPTOR_H
#define GRLIB_CGLIBSAMPLERDESCRIPTOR_H

#include "nvn/nvn.h"
#include "grlib/CGLibBuffFixAlloc.h"
#include "grlib/CGLibMemPool.h"

namespace grlib {
class CGLibSampler;

// an NVN sampler as the descriptors register it (the name is the original's, the layout is not known beyond it)
class CGLibSamplerParam {
public:
    NVNsampler m_sampler;  // 0x0
};

// the platform part of the sampler descriptor pool (a base at 0x28; the field names are not the original's)
class CGLibSamplerDescriptor_plf {
public:
    void bindSampler(const CGLibSamplerParam& param, int samplerId);
    // the pool slot of the sampler's id
    int setSampler(const CGLibSampler& sampler);

    CGLibMemPool m_pool;              // 0x0
    NVNsamplerPool m_samplerPool;     // 0x20
};

class CGLibSamplerDescriptor : public CGLibBuffFixAlloc, public CGLibSamplerDescriptor_plf {
public:
    CGLibSamplerDescriptor();
    ~CGLibSamplerDescriptor();
    void release();
    // initializes the sampler pool on `pool` at `offset` with `num` descriptors; the bytes it takes
    unsigned int setup(CGLibMemPool& pool, unsigned int offset, unsigned int num);
    // sets the sampler pool on the pipeline's command buffer
    void bind();
};
}  // namespace grlib

#endif
