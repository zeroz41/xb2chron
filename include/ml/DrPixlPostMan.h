#ifndef ML_DRPIXLPOSTMAN_H
#define ML_DRPIXLPOSTMAN_H

#include "grlib/CGLibRenderTarget.h"

namespace grlib { class CGLibTextureBuffer; }
namespace ml { class DrPixlPostObjCubeMapIBL; }
namespace ml { class DrPixlSkyDome; }
namespace ml { class DrPixlToonGrad; }
namespace ml { class DrPixlPostObjCapture; }

namespace ml {
// DrPixlObjTbl::m_postMan. Only what DrMdoSetup reads is known; the field names are not the original's.
class DrPixlPostMan {
public:
    grlib::CGLibRenderTarget* getDownDepth();
    grlib::CGLibRenderTarget* getOldDownDepth();
    void setDownDepth();
    bool isDepthDown();
    // Parameter names inferred, not the original's: each turns on one render target (+0xD0, the half-size +0xD8).
    void renderRefractionMap(bool useTarget, bool useHalfTarget);
    grlib::CGLibTextureBuffer* getToonGradTex() const;
    grlib::CGLibTextureBuffer* getToonDarkGradTex() const;

    unsigned char pad_0[0x48];
    DrPixlPostObjCubeMapIBL* m_cubeMapIBL;  // 0x48, varStTex_SpecularIBLTex binds its premultiplied texture
    unsigned char pad_50[0x40];
    DrPixlSkyDome* m_skyDome;  // 0x90, DrPixlMan::renderSkyDome/renderSkyGodRay when set
    DrPixlToonGrad* m_toonGrad;  // 0x98, getToonGradTex/getToonDarkGradTex when set
    unsigned char pad_A0[0x10];
    DrPixlPostObjCapture* m_capture;  // 0xB0, DrPixlMan::lastCapRender when set
    unsigned char pad_B8[0x8];
    grlib::CGLibRenderTarget* m_downDepth[2];  // 0xC0, getDownDepth by DrMan::s_nDblIdx, getOldDownDepth by s_nDblStockIdx
    grlib::CGLibRenderTarget* m_refraction;  // 0xD0, varStTex_RefractionMap/RefractionAfterTex bind it when set
    unsigned char pad_D8[0x20];
    unsigned int m_flags;  // 0xF8, setDownDepth sets 0x80000, isDepthDown tests it
    unsigned char pad_FC[0xC];
    float m_waterFog;  // 0x108, below 0.05 varStTex_DownBaseColorTex binds the dummy texture; matCall_WaterFog reads it
};
}  // namespace ml

#endif
