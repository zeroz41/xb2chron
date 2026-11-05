#ifndef ML_DRPIXLPOSTMAN_H
#define ML_DRPIXLPOSTMAN_H

#include "grlib/CGLibRenderTarget.h"
#include "ml/DrPixlRenderTarget.h"

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
namespace ml { class DrPixlPostObjToneMap; class DrPixlPostObjBloom; class DrPixlPostObjFxAA; class DrPixlPostObjHistgram; class DrPixlPostObjTMAA; class DrPixlPostObjRainDrop; class DrPixlPostObjGlassBr; }
namespace ml { class DrPixlPostObjSSR; class DrPixlPostObjTSSAO; class DrPixlPostObjExpStencil; class DrPixlShadowRaytrace; class DrPixlPostObjUnbranchToDepth; }

namespace ml {
// DrPixlObjTbl::m_postMan. Only what DrMdoSetup reads is known; the field names are not the original's.
class DrPixlPostMan {
public:
    // m_volumeWork's render volume: a CGLibRenderVolume that keeps its DrMan (inline constructor and destructor; no
    // symbol, the name is not the original's)
    class RenderVolume : public grlib::CGLibRenderVolume {
    public:
        RenderVolume(DrMan* drMan) { m_drMan = drMan; }
        ~RenderVolume() { releaseWork(); }

        DrMan* m_drMan;  // 0x90
    };
    // m_volumeWork (0x30 bytes, inline constructor and destructor; no symbol, the names are not the original's): the
    // managers and two 16x16x16 render volumes
    class VolumeWork {
    public:
        inline VolumeWork(DrMan* drMan, DrPixlMan* pixlMan, DrPixlPostMan* postMan);  // DrPixlMan.cpp
        ~VolumeWork() {
            for (int i = 0; i < 2; i++) {
                if (m_volume[i] != nullptr) {
                    delete m_volume[i];
                    m_volume[i] = nullptr;
                }
            }
        }

        DrMan* m_drMan;  // 0x0
        DrPixlMan* m_pixlMan;  // 0x8
        DrPixlPostMan* m_postMan;  // 0x10
        bool m_flag;  // 0x18, the constructor clears it
        unsigned char pad_19[0x7];
        RenderVolume* m_volume[2];  // 0x20
    };

    DrPixlPostMan(DrMan* drMan, DrPixlMan* pixlMan, int);
    ~DrPixlPostMan();
    grlib::CGLibRenderTarget* getDownDepth();
    grlib::CGLibRenderTarget* getOldDownDepth();
    void setDownDepth();
    bool isDepthDown();
    // Parameter names inferred, not the original's: each turns on one render target (+0xD0, the half-size +0xD8).
    void renderRefractionMap(bool useTarget, bool useHalfTarget);
    void render();
    void renderDeferredFast();
    void renderDownDepth(bool, bool, bool);
    grlib::CGLibTextureBuffer* getToonGradTex() const;
    grlib::CGLibTextureBuffer* getToonDarkGradTex() const;
    void setVolumePos(const mm::Vec3& pos);
    // on: sets 0x80040 in m_flags and creates m_motionBlur2; off (when 0x40 is set): deletes both blurs, clears 0x40
    void setBlur(bool on);
    // on: sets 0x80020 in m_flags and creates m_depthOfField; off (when 0x20 is set): clears 0x20, deletes it
    void setDepthField(bool on);
    void resetColorBuff();
    void setupDepthBuff();
    void update();

    DrMan* m_drMan;  // 0x0 (name inferred)
    DrPixlMan* m_pixlMan;  // 0x8 (name inferred)
    VolumeWork* m_volumeWork;  // 0x10 (name inferred)
    // 0x18, update runs updateByCompute or updateByRenderTarget on it (name inferred)
    DrPixlPostObjToneMap* m_toneMap;
    DrPixlPostObjBloom* m_bloom;  // 0x20, resetColorBuff resets it (name inferred)
    DrPixlPostObjVolume* m_volume;  // 0x28, the constructor creates it; setVolumePos writes its position (name inferred)
    DrPixlPostObjDepthofField* m_depthOfField;  // 0x30, setDepthField (name inferred)
    DrPixlPostObjFxAA* m_fxaa;  // 0x38, render calls its calcScale (name inferred)
    DrPixlPostObjCubeMapMultiIBL* m_cubeMapMultiIBL;  // 0x40, DrPixlMan::fastRender renders it when set (name inferred)
    DrPixlPostObjCubeMapIBL* m_cubeMapIBL;  // 0x48, varStTex_SpecularIBLTex binds its premultiplied texture
    DrPixlPostObjMotionBlur* m_motionBlur;  // 0x50, setBlur deletes it (name inferred)
    DrPixlPostObjMotionBlur2* m_motionBlur2;  // 0x58, setBlur creates and deletes it (name inferred)
    DrPixlPostObjHistgram* m_histgram;  // 0x60, update updates it when set (name inferred)
    DrPixlPostObjTMAA* m_tmaa;  // 0x68, resetColorBuff resets it when set (name inferred)
    // 0x70..0x88: renderDeferredFast renders each when set (names inferred)
    DrPixlPostObjSSR* m_ssr;  // 0x70
    DrPixlPostObjTSSAO* m_tssao;  // 0x78
    DrPixlPostObjExpStencil* m_expStencil;  // 0x80
    DrPixlShadowRaytrace* m_shadowRaytrace;  // 0x88
    DrPixlSkyDome* m_skyDome;  // 0x90, DrPixlMan::renderSkyDome/renderSkyGodRay when set
    DrPixlToonGrad* m_toonGrad;  // 0x98, getToonGradTex/getToonDarkGradTex when set
    DrPixlPostObjRainDrop* m_rainDrop;  // 0xA0 (name inferred)
    DrPixlPostObjGlassBr* m_glassBr;  // 0xA8 (name inferred)
    DrPixlPostObjCapture* m_capture;  // 0xB0, DrPixlMan::lastCapRender when set
    DrPixlPostObjUnbranchToDepth* m_unbranchToDepth;  // 0xB8, renderDeferredFast renders it when set (name inferred)
    DrPixlRenderTarget* m_downDepth[2];  // 0xC0, getDownDepth by DrMan::s_nDblIdx, getOldDownDepth by s_nDblStockIdx
    DrPixlRenderTarget* m_refraction;  // 0xD0, varStTex_RefractionMap/RefractionAfterTex bind it when set
    DrPixlRenderTarget* m_refractionHalf;  // 0xD8, the half-size refraction target (name inferred)
    // 0xE0, setupDepthBuff sets it up at a quarter size with DrPixlFormat::s_QuaterNormalFormat (name inferred)
    DrPixlRenderTarget* m_quaterNormal;
    DrPixlRenderTarget* m_depthBuff;  // 0xE8, setupDepthBuff: DrPixlFormat::s_DepthBufferFormat (name inferred)
    DrResUseQueryObj* m_refractionQuery;  // 0xF0, DrPixlMan::renderRefractionEnd ends it when set (name inferred)
    unsigned int m_flags;  // 0xF8, setDownDepth sets 0x80000, isDepthDown tests it; 0x10000: DrPixlMan::setupGodRay
    unsigned char pad_FC[0xC];
    float m_waterFog;  // 0x108, below 0.05 varStTex_DownBaseColorTex binds the dummy texture; matCall_WaterFog reads it
};
}  // namespace ml

#endif
