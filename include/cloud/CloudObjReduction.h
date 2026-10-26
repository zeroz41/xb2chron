#ifndef CLOUD_CLOUDOBJREDUCTION_H
#define CLOUD_CLOUDOBJREDUCTION_H

#include "grlib/CGLibRenderTarget.h"

namespace cloud {
// 0x2B58 (CloudObjMan allocates it). Field names are not the original's.
class CloudObjReduction {
public:
    CloudObjReduction();
    ~CloudObjReduction();
    void imgUpdate();
    void update();
    void alphaFastRender();

    // returns s_nPixelOfs (CloudMan::getPixelMem forwards to it unchanged, so it is static)
    static unsigned int getPixelMem(unsigned int& mem, unsigned int width, unsigned int height);

    unsigned char pad_0[0xF90];
    grlib::CGLibRenderTarget m_skyTarget;  // 0xF90, CloudObjSky::alphaRender clears it before renderSkyPoli
    grlib::CGLibRenderTarget m_mdlTarget;  // 0x1358, CloudObjMdl::alphaRender clears it before renderBaseMdlPoli
    unsigned char pad_1720[0x1438];
};
}  // namespace cloud

#endif
