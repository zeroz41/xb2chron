#ifndef GRLIB_CGLIBSAMPLER_H
#define GRLIB_CGLIBSAMPLER_H

#include "grlib/GrlTypes.h"

namespace grlib {

// a texture sampler (0x20 bytes): set up by initSampler/setClamp, made current by updateData
class CGLibSampler {
public:
    CGLibSampler();
    ~CGLibSampler();
    void initSampler(GrlTexClamp clamp, GrlTexMagFilterType filter);
    void setClamp(GrlTexClamp s, GrlTexClamp t, GrlTexClamp r);
    void updateData();

    unsigned char pad_0[0x20];
};

}  // namespace grlib

#endif
