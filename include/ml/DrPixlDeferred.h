#ifndef ML_DRPIXLDEFERRED_H
#define ML_DRPIXLDEFERRED_H

namespace grlib { class CGLibTextureBuffer; }
namespace ml { class DrMan; class DrShdMan; class DrPixlMan; class DrPixlRenderTarget; }

namespace ml {
// DrPixlObjTbl::m_deferred. Only what DrMdoSetup and DrPixlMan call is declared.
class DrPixlDeferred {
public:
    ~DrPixlDeferred();
    void debugRender();
    void lgtCalcRender();
    grlib::CGLibTextureBuffer* getShadowMapTexture() const;
    void displayUpdate();
    void lastDeferredRender();

    // the constructor stores the fields below and creates the three render targets (the field names are not the
    // original's)
    unsigned char pad_0[0x8];  // 0x0, the constructor clears it
    DrMan* m_drMan;  // 0x8
    DrShdMan* m_shdMan;  // 0x10, DrMan::m_shdMan
    DrPixlMan* m_pixlMan;  // 0x18
    // 0x20, set up with DrPixlFormat::s_DirShadowFormat; getShadowMapTexture's single-buffered shadow map
    DrPixlRenderTarget* m_shadowTarget;
    // 0x28, getShadowMapTexture by DrMan::s_nDblIdx while both DrPixlPostParm::m_shadowMapDbl are set
    DrPixlRenderTarget* m_shadowTargetDbl[2];
    unsigned char pad_38[0x4];  // 0x38, the constructor stores 0x10001
};
}  // namespace ml

#endif
