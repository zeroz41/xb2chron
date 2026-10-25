#ifndef GRLIB_CGLIBSAMPLER_H
#define GRLIB_CGLIBSAMPLER_H

#include "grlib/GrlTypes.h"
#include "grlib/CGLibBuffSamplerTbl.h"

namespace mm { struct Col4; }

namespace grlib {

// a texture sampler (0x20 bytes): its state, and the shared sampler object updateData takes for it from the
// context's CGLibBuffSamplerTbl (the field names are not the original's)
class CGLibSampler {
public:
    CGLibSampler();
    ~CGLibSampler();
    void release();
    void initSampler(GrlTexClamp clamp, GrlTexMagFilterType filter);
    void setClamp(GrlTexClamp s, GrlTexClamp t, GrlTexClamp r);
    void setFilter(GrlTexMagFilterType mag, GrlTexMinFilterType min, GrlTexTexAnisoRatio aniso);
    void setLOD(float lod);
    void setDepthCompare(GrlTexCompare compare);
    void setBorderType(GrlTexBorderType type);
    void setBorderColor(const mm::Col4& color);
    void updateData();

    CGLibWkrSamplerParams m_params;  // 0x00
    CGLibBuffResSamObj* m_pSamObj;   // 0x18
};

}  // namespace grlib

#endif
