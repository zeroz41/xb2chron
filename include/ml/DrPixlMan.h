#ifndef ML_DRPIXLMAN_H
#define ML_DRPIXLMAN_H

#include "grlib/CGLibRenderTarget.h"

namespace grlib { class CGLibTextureBuffer; }
namespace ml { class DrPixlDeferred; }
namespace ml { class DrPixlPostMan; }
namespace ml { class DrMan; }
namespace ml { class DrPixlRenderTarget; }
namespace ml { class DrPixlShadowObj; }
namespace ml { class DrPixlOccQuery; }
namespace ml { class DrPixlShadowCacheMan; }
namespace ml { class DrPixlShadowMan; }
namespace grlib { class CGLibDblUniformBlock; }

namespace ml {
// DrPixlMan::m_objTbl: getPixlObj(i) reads entry i (two pointers per entry, the second double-buffered); the
// entries DrMdoSetup reads by name are below. The type and field names are not the original's.
// DrPixlMan::setupCate points m_objTbl at one of four entries 0x1F8 bytes apart from DrPixlMan+0x10.
// The table is really 0x10-byte entries of two object pointers (getPixlObj(i): entry i, the second pointer for the
// double-buffered entries 17, 20, 21, 22, 25 by DrMan::s_nDblIdx); the fields below name what callers read.
struct DrPixlObjTbl {
  union {
    // getPixlObj(i): entry i; the double-buffered entries (9, 12, 13, 14, 17) by DrMan::s_nDblIdx
    grlib::CGLibRenderTarget* m_obj[31][2];
    struct {
    grlib::CGLibRenderTarget* m_gBuff[5][2];  // 0x0, refractionGBuffInvalidate invalidates [i][0]
    unsigned char pad_50[0xD0];
    grlib::CGLibRenderTarget* m_responsiveAAMask;  // 0x120, getResponsiveAAMask
    unsigned char pad_128[0x10];
    DrPixlRenderTarget* m_hdrBuff[2];  // 0x138, changeHDRBuff
    grlib::CGLibRenderTarget* m_backFaceDepth;  // 0x148, getBackFaceDepthTexture
    unsigned char pad_150[0x20];
    DrPixlDeferred* m_deferred;  // 0x170
    DrPixlShadowMan* m_shadowMan;  // 0x178, the light objects release their shadow through it (the name is not the original's)
    DrPixlPostMan* m_postMan;  // 0x180
    // 0x188, DrPixlPostObjToneMap::updateByCompute stores the three; the constructor sets [1] = 1 (name inferred)
    float m_toneMapVal[3];
    unsigned char pad_194[0xC];
    grlib::CGLibRenderTarget* m_depth[2];  // 0x1A0, getDepthObj: by DrMan::s_nDblIdx
    unsigned char pad_1B0[0x20];
    grlib::CGLibRenderTarget* m_capture;  // 0x1D0, renderEnd invalidates its colour
    unsigned int m_flags;  // 0x1D8, updateShadowDisplayList clears 0x20
    unsigned char pad_1DC[0x1C];
    };
  };
};

// DrMan's pixel manager (DrMan::m_pixlMan). Only what DrMdoSetup's texture callbacks read is known; the field
// names are not the original's. The capture and movie fields are read by DrMdoSetup::varStTex_Capture*/Movie*.
class DrPixlMan {
public:
    DrPixlMan(DrMan* drMan);
    ~DrPixlMan();
    void createColorBuffer();
    static DrPixlMan* get();
    void releaseColorBuffer();
    void occRenderEnd();
    void depCheckEnd();
    void callFgShadowCacheUpdate();
    void setMainSRGBRenderTarget();
    void resetRenderTarget();
    void alphaRenderTarget();
    void callShadowCacheVariance();
    void selectGBuffRenderTarget();
    void selectGBuffRenderTarget(unsigned int target);
    grlib::CGLibRenderTarget* getResponsiveAAMask();
    void displayUpdate();
    void thicknessFirstEnd();
    void refractionGBuffInvalidate();
    void lastDeferredRender();
    void renderEnd(int);
    void renderRefractionMap(bool useTarget, bool useHalfTarget);
    void renderSkyDome();
    void renderSkyGodRay();
    bool isRefractionMap();
    void lastCapRender();
    grlib::CGLibRenderTarget* getDepthObj();
    void changeHDRBuff(DrPixlRenderTarget* target);
    void setShadowObj(DrPixlShadowObj* obj);
    void updateShadowDisplayList();
    void shadowDirBegin();
    grlib::CGLibRenderTarget* getPixlObj(int index);
    grlib::CGLibTextureBuffer* getDammyTexObj();       // reads m_dammyObj's texture
    grlib::CGLibTextureBuffer* getDammyWhiteTexObj();  // reads m_dammyWhiteObj's texture
    grlib::CGLibRenderTarget* getBackFaceDepthTexture();
    grlib::CGLibRenderTarget* getDiffIBLObj();
    grlib::CGLibRenderTarget* getSpecIBLObj();
    grlib::CGLibRenderTarget* getDeactivePixlObj(int index);
    void setupCate(int cate);

    float m_rate;  // 0x0, the constructor sets 1.0f; no reader in this unit is known (name inferred)
    unsigned char pad_4[0x4];
    DrMan* m_drMan;  // 0x8, shadowDirBegin reaches DrMan::m_apCache through it
    // 0x10, one table per category; setupCate points m_objTbl at one. varStTex_Capture* read
    // m_cate[0..3].m_capture (main, 1, 2, 3).
    DrPixlObjTbl m_cate[4];
    DrPixlObjTbl* m_objTbl;  // 0x7F0
    DrPixlOccQuery* m_occQuery;  // 0x7F8, DrPixlSkyDome::godRayRender passes it to DrResUseQueryObj::begin
    DrPixlShadowCacheMan* m_shadowCacheMan;  // 0x800, fastRender calls shadowCacheRender on it
    grlib::CGLibTextureBuffer* m_movieTex[4];  // 0x808
    bool m_movieFilter[4];  // 0x828, true: varStTex_Movie* sample with filter mode 1, else 0
    grlib::CGLibRenderTarget* m_dammyObj;  // 0x830, getDammyTexObj
    grlib::CGLibRenderTarget* m_dammyWhiteObj;  // 0x838, getDammyWhiteTexObj
    bool m_clearTarget;  // 0x840, renderBegin clears the targets once while set; releaseColorBuffer sets it
    unsigned char pad_841[0x7];
    DrPixlShadowObj* m_shadowObj;  // 0x848, setShadowObj
    grlib::CGLibDblUniformBlock* m_shadowUniform;  // 0x850, setShadowObj: the object's uniform block
    int m_renderTarget;  // 0x858, resetRenderTarget clears it
    int m_renderTargetSub;  // 0x85C, cleared and set together with m_renderTarget (name inferred)
    int m_cateIdx;  // 0x860, setupCate stores the category (name inferred)
    unsigned char pad_864[0x15C];
    grlib::CGLibRenderTarget* m_capture4;  // 0x9C0
};
}  // namespace ml

#endif
