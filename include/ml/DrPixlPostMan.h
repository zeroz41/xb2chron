#ifndef ML_DRPIXLPOSTMAN_H
#define ML_DRPIXLPOSTMAN_H

#include "grlib/CGLibRenderTarget.h"

namespace grlib { class CGLibTextureBuffer; }
namespace ml { class DrPixlPostObjCubeMapIBL; }
namespace ml { class DrPixlPostObjCubeMapMultiIBL; }
namespace ml { class DrPixlSkyDome; }
namespace ml { class DrPixlToonGrad; }
namespace ml { class DrResUseQueryObj; }
namespace ml { class DrPixlPostObjVolume; }
namespace mm { class Vec3; }
namespace ml { class DrMan; class DrPixlMan; class DrPixlPostObjDepthofField; class DrPixlPostObjMotionBlur; class DrPixlPostObjMotionBlur2; }
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
    void setVolumePos(const mm::Vec3& pos);
    // on: sets 0x80040 in m_flags and creates m_motionBlur2; off (when 0x40 is set): deletes both blurs, clears 0x40
    void setBlur(bool on);
    // on: sets 0x80020 in m_flags and creates m_depthOfField; off (when 0x20 is set): clears 0x20, deletes it
    void setDepthField(bool on);

    DrMan* m_drMan;  // 0x0 (name inferred)
    DrPixlMan* m_pixlMan;  // 0x8 (name inferred)
    unsigned char pad_10[0x18];
    DrPixlPostObjVolume* m_volume;  // 0x28, the constructor creates it; setVolumePos writes its position (name inferred)
    DrPixlPostObjDepthofField* m_depthOfField;  // 0x30, setDepthField (name inferred)
    unsigned char pad_38[0x8];
    DrPixlPostObjCubeMapMultiIBL* m_cubeMapMultiIBL;  // 0x40, DrPixlMan::fastRender renders it when set (name inferred)
    DrPixlPostObjCubeMapIBL* m_cubeMapIBL;  // 0x48, varStTex_SpecularIBLTex binds its premultiplied texture
    DrPixlPostObjMotionBlur* m_motionBlur;  // 0x50, setBlur deletes it (name inferred)
    DrPixlPostObjMotionBlur2* m_motionBlur2;  // 0x58, setBlur creates and deletes it (name inferred)
    unsigned char pad_60[0x30];
    DrPixlSkyDome* m_skyDome;  // 0x90, DrPixlMan::renderSkyDome/renderSkyGodRay when set
    DrPixlToonGrad* m_toonGrad;  // 0x98, getToonGradTex/getToonDarkGradTex when set
    unsigned char pad_A0[0x10];
    DrPixlPostObjCapture* m_capture;  // 0xB0, DrPixlMan::lastCapRender when set
    unsigned char pad_B8[0x8];
    grlib::CGLibRenderTarget* m_downDepth[2];  // 0xC0, getDownDepth by DrMan::s_nDblIdx, getOldDownDepth by s_nDblStockIdx
    grlib::CGLibRenderTarget* m_refraction;  // 0xD0, varStTex_RefractionMap/RefractionAfterTex bind it when set
    unsigned char pad_D8[0x18];
    DrResUseQueryObj* m_refractionQuery;  // 0xF0, DrPixlMan::renderRefractionEnd ends it when set (name inferred)
    unsigned int m_flags;  // 0xF8, setDownDepth sets 0x80000, isDepthDown tests it; 0x10000: DrPixlMan::setupGodRay
    unsigned char pad_FC[0xC];
    float m_waterFog;  // 0x108, below 0.05 varStTex_DownBaseColorTex binds the dummy texture; matCall_WaterFog reads it
};
}  // namespace ml

#endif
