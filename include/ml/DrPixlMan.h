#ifndef ML_DRPIXLMAN_H
#define ML_DRPIXLMAN_H

#include "grlib/CGLibRenderTarget.h"

namespace grlib { class CGLibTextureBuffer; }
namespace ml { class DrPixlDeferred; }
namespace ml { class DrPixlPostMan; }
namespace ml { class DrMan; }
namespace ml { class DrPixlRenderTarget; }
namespace ml { class DrPixlShadowObj; }
namespace grlib { class CGLibDblUniformBlock; }

namespace ml {
// DrPixlMan::m_objTbl: getPixlObj(i) reads entry i (two pointers per entry, the second double-buffered); the
// entries DrMdoSetup reads by name are below. The type and field names are not the original's.
// DrPixlMan::setupCate points m_objTbl at one of four entries 0x1F8 bytes apart from DrPixlMan+0x10.
// The table is really 0x10-byte entries of two object pointers (getPixlObj(i): entry i, the second pointer for the
// double-buffered entries 17, 20, 21, 22, 25 by DrMan::s_nDblIdx); the fields below name what callers read.
struct DrPixlObjTbl {
    grlib::CGLibRenderTarget* m_gBuff[5][2];  // 0x0, refractionGBuffInvalidate invalidates [i][0]
    unsigned char pad_50[0xD0];
    grlib::CGLibRenderTarget* m_responsiveAAMask;  // 0x120, getResponsiveAAMask
    unsigned char pad_128[0x10];
    DrPixlRenderTarget* m_hdrBuff[2];  // 0x138, changeHDRBuff
    grlib::CGLibRenderTarget* m_backFaceDepth;  // 0x148, getBackFaceDepthTexture
    unsigned char pad_150[0x20];
    DrPixlDeferred* m_deferred;  // 0x170
    unsigned char pad_178[0x8];
    DrPixlPostMan* m_postMan;  // 0x180
    unsigned char pad_188[0x18];
    grlib::CGLibRenderTarget* m_depth[2];  // 0x1A0, getDepthObj: by DrMan::s_nDblIdx
    unsigned char pad_1B0[0x20];
    grlib::CGLibRenderTarget* m_capture;  // 0x1D0, renderEnd invalidates its colour
    unsigned int m_flags;  // 0x1D8, updateShadowDisplayList clears 0x20
    unsigned char pad_1DC[0x1C];
};

// DrMan's pixel manager (DrMan::m_pixlMan). Only what DrMdoSetup's texture callbacks read is known; the field
// names are not the original's. The capture and movie fields are read by DrMdoSetup::varStTex_Capture*/Movie*.
class DrPixlMan {
public:
    ~DrPixlMan();
    static DrPixlMan* get();
    void releaseColorBuffer();
    void occRenderEnd();
    void depCheckEnd();
    void callFgShadowCacheUpdate();
    void setMainSRGBRenderTarget();
    void resetRenderTarget();
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

    unsigned char pad_0[0x8];
    DrMan* m_drMan;  // 0x8, shadowDirBegin reaches DrMan::m_apCache through it
    unsigned char pad_10[0x1D0];
    grlib::CGLibRenderTarget* m_captureMain;  // 0x1E0
    unsigned char pad_1E8[0x1F0];
    grlib::CGLibRenderTarget* m_capture1;  // 0x3D8
    unsigned char pad_3E0[0x1F0];
    grlib::CGLibRenderTarget* m_capture2;  // 0x5D0
    unsigned char pad_5D8[0x1F0];
    grlib::CGLibRenderTarget* m_capture3;  // 0x7C8
    unsigned char pad_7D0[0x20];
    DrPixlObjTbl* m_objTbl;  // 0x7F0
    unsigned char pad_7F8[0x10];
    grlib::CGLibTextureBuffer* m_movieTex[4];  // 0x808
    bool m_movieFilter[4];  // 0x828, true: varStTex_Movie* sample with filter mode 1, else 0
    grlib::CGLibRenderTarget* m_dammyObj;  // 0x830, getDammyTexObj
    grlib::CGLibRenderTarget* m_dammyWhiteObj;  // 0x838, getDammyWhiteTexObj
    unsigned char pad_840[0x8];
    DrPixlShadowObj* m_shadowObj;  // 0x848, setShadowObj
    grlib::CGLibDblUniformBlock* m_shadowUniform;  // 0x850, setShadowObj: the object's uniform block
    int m_renderTarget;  // 0x858, resetRenderTarget clears it
    unsigned char pad_85C[0x164];
    grlib::CGLibRenderTarget* m_capture4;  // 0x9C0
};
}  // namespace ml

#endif
