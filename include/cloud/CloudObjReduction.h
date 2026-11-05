#ifndef CLOUD_CLOUDOBJREDUCTION_H
#define CLOUD_CLOUDOBJREDUCTION_H

#include "grlib/CGLibRenderTarget.h"
#include "grlib/CGLibPixlCounter.h"
#include "cloud/CloudUniform.h"

namespace cloud {
// 0x2B58 (CloudObjMan allocates it). The layout is the constructor's and the destructor's; field names are not the
// original's.
class CloudObjReduction {
public:
    CloudObjReduction();
    ~CloudObjReduction();
    void imgUpdate();
    void update();
    void alphaFastRender();
    void renderUpScale(grlib::CGLibRenderTarget& target);
    void counterRender(bool plane, bool mdl);
    void depthRender(bool);
    void stencilRender();

    // returns s_nPixelOfs (CloudMan::getPixelMem forwards to it unchanged, so it is static)
    static unsigned int getPixelMem(unsigned int& mem, unsigned int width, unsigned int height);

    // getPixelMem's pixel offsets of the targets imgUpdate sets up (depth 0, depth 1, sky/mdl, then 0x70, 0x438,
    // 0x800, 0xBC8, 0x1720)
    static unsigned int s_nPixelOfs[8];

    CloudUniform m_uniform0;               // 0x0, CLOUD_UNIFORM_15
    CloudUniform m_uniform1;               // 0x38, CLOUD_UNIFORM_16 ("U_DOWN" in depthRender)
    grlib::CGLibRenderTarget m_target0;    // 0x70, alphaFastRender clears it
    grlib::CGLibRenderTarget m_target1;    // 0x438
    grlib::CGLibRenderTarget m_target2;    // 0x800
    grlib::CGLibRenderTarget m_target3;    // 0xBC8
    grlib::CGLibRenderTarget m_skyTarget;  // 0xF90, CloudObjSky::alphaRender clears it before renderSkyPoli
    grlib::CGLibRenderTarget m_mdlTarget;  // 0x1358, CloudObjMdl::alphaRender clears it before renderBaseMdlPoli
    grlib::CGLibRenderTarget m_upTarget;   // 0x1720, renderUpScale draws to it (twice the width)
    grlib::CGLibDepthTarget m_depth0;      // 0x1AE8
    grlib::CGLibDepthTarget m_depth1;      // 0x22E8
    grlib::CGLibPixlCounter m_counter[4];  // 0x2AE8 ("U_COUNT1".."U_COUNT4")
    int m_width;                           // 0x2B48, -1 from the constructor
    int m_height;                          // 0x2B4C, -1 from the constructor
    int m_isUpdate;                        // 0x2B50, update sets it to 1
    bool m_isReady;                        // 0x2B54, false from the constructor (the name is a guess)
};
}  // namespace cloud

#endif
