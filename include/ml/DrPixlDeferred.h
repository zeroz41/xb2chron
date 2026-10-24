#ifndef ML_DRPIXLDEFERRED_H
#define ML_DRPIXLDEFERRED_H

namespace grlib { class CGLibTextureBuffer; }

namespace ml {
// DrPixlObjTbl::m_deferred. Only what DrMdoSetup calls is declared.
class DrPixlDeferred {
public:
    grlib::CGLibTextureBuffer* getShadowMapTexture() const;
};
}  // namespace ml

#endif
