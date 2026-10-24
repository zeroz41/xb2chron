#ifndef ML_DRPIXLPOSTOBJCUBEMAPIBL_H
#define ML_DRPIXLPOSTOBJCUBEMAPIBL_H

namespace grlib { class CGLibTextureBuffer; }

namespace ml {
// DrPixlPostMan::m_cubeMapIBL. Only what DrMdoSetup calls is declared.
class DrPixlPostObjCubeMapIBL {
public:
    grlib::CGLibTextureBuffer* getPremTexture() const;
};
}  // namespace ml

#endif
