#ifndef CLASSES_PTLIB_MATERIAL_MATERIALTEXTURE_H
#define CLASSES_PTLIB_MATERIAL_MATERIALTEXTURE_H

#include "grlib/CGLibTextureBuffer.h"
#include "ptlib/material/MaterialBase.h"

namespace ptlib { namespace material {
// table 0x7100B807D0; a texture MaterialManager makes (the field names are not the original's)
class MaterialTexture : public MaterialBase {
public:
    // the type and the 3D flag are assigned in the body: the original stores them after the texture's construction
    MaterialTexture() {
        m_type = 0;
        m_is3D = false;
    }
    virtual ~MaterialTexture();  // slot 0

    bool m_is3D;  // MaterialManager::createTexture's: the image is a 3D texture
    grlib::CGLibTextureBuffer m_texture;  // ScreenRenderManager::RenderScreenDebug draws with it
};
}}  // namespace ptlib::material

#endif
