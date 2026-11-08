#ifndef ML_DRPIXLDEFERRED_H
#define ML_DRPIXLDEFERRED_H

namespace grlib { class CGLibTextureBuffer; }
namespace ml { class DrMan; class DrShdMan; class DrPixlMan; class DrPixlRenderTarget; }

namespace ml {
// wkPixlManRes::m_deferred. Only what DrMdoSetup and DrPixlMan call is declared.
class DrPixlDeferred {
public:
    DrPixlDeferred(DrMan* drMan, DrPixlMan* pixlMan);
    ~DrPixlDeferred();
    void resetColorBuff();
    // false when no shadow was rendered
    bool shadowTexRender(int);
    void shadowBuffCacheRender();
    bool shadowBuffDefRender();
    void debugRender();
    void lgtCalcRender();
    grlib::CGLibTextureBuffer* getShadowMapTexture() const;
    void displayUpdate();
    void lastDeferredRender();
    void fastDeferredRender(int);

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
    // 0x38: the size the shadow targets were last set up with (displayUpdate redoes them when it changes); the
    // constructor sets 1, 1, resetColorBuff 0, 0 (the names are not the original's)
    short m_shadowWidth;
    short m_shadowHeight;  // 0x3A
};
}  // namespace ml

#endif
