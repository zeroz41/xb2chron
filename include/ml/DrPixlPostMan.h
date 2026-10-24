#ifndef ML_DRPIXLPOSTMAN_H
#define ML_DRPIXLPOSTMAN_H

#include "grlib/CGLibRenderTarget.h"

namespace grlib { class CGLibTextureBuffer; }
namespace ml { class DrPixlPostObjCubeMapIBL; }

namespace ml {
// DrPixlObjTbl::m_postMan. Only what DrMdoSetup reads is known; the field names are not the original's.
class DrPixlPostMan {
public:
    grlib::CGLibRenderTarget* getDownDepth();
    grlib::CGLibTextureBuffer* getToonGradTex() const;
    grlib::CGLibTextureBuffer* getToonDarkGradTex() const;

    unsigned char pad_0[0x48];
    DrPixlPostObjCubeMapIBL* m_cubeMapIBL;  // 0x48, varStTex_SpecularIBLTex binds its premultiplied texture
    unsigned char pad_50[0x80];
    grlib::CGLibRenderTarget* m_refraction;  // 0xD0, varStTex_RefractionMap/RefractionAfterTex bind it when set
    unsigned char pad_D8[0x30];
    float m_waterFog;  // 0x108, below 0.05 varStTex_DownBaseColorTex binds the dummy texture; matCall_WaterFog reads it
};
}  // namespace ml

#endif
