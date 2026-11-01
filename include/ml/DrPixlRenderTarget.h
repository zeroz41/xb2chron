#ifndef ML_DRPIXLRENDERTARGET_H
#define ML_DRPIXLRENDERTARGET_H

#include "grlib/CGLibRenderTarget.h"

namespace ml { class DrMan; }

namespace ml {
// a render target that keeps its DrMan (DrPixlMan.cpp defines it; the field name is not the original's)
class DrPixlRenderTarget : public grlib::CGLibRenderTarget {
public:
    DrPixlRenderTarget(DrMan* drMan);
    ~DrPixlRenderTarget();

    DrMan* m_drMan;  // 0x3C8
};

// a mip-mapped cube map render target that keeps its DrMan (DrPixlMan.cpp defines it; the field name is not the
// original's)
class DrPixlRenderCubeMapMipMap : public grlib::CGLibRenderCubeMapMipMap {
public:
    DrPixlRenderCubeMapMipMap(DrMan* drMan);
    ~DrPixlRenderCubeMapMipMap();

    DrMan* m_drMan;  // 0x1888
};
}  // namespace ml

#endif
