#ifndef ML_DRPIXLDEFERRED_H
#define ML_DRPIXLDEFERRED_H

namespace grlib { class CGLibTextureBuffer; }

namespace ml {
// DrPixlObjTbl::m_deferred. Only what DrMdoSetup and DrPixlMan call is declared.
class DrPixlDeferred {
public:
    grlib::CGLibTextureBuffer* getShadowMapTexture() const;
    void displayUpdate();
    void lastDeferredRender();
};
}  // namespace ml

#endif
