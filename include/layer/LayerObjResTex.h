#ifndef LAYER_LAYEROBJRESTEX_H
#define LAYER_LAYEROBJRESTEX_H

#include "layer/LayerLinkList.h"
#include "layer/LayerResAddTexObj.h"

namespace grlib { class CGLibTextureBuffer; }

namespace layer {
class LayerTextureObj;

// the added textures of a LayerObjTopDef (0x2C0) or LayerObjTopPolyObj (0x2B8): 0x48 bytes, the next field of
// both follows it. clear() deletes the objects of its three lists (0x0, 0x18, 0x30; what each list holds is not
// known yet, the names are not the original's).
class LayerObjResTex {
public:
    void setAddTexture(const void* res, unsigned int index);
    void setAddTexture(grlib::CGLibTextureBuffer& texture, unsigned int index);
    void clear();
    void updateTexutre(grlib::CGLibTextureBuffer** textures, LayerTextureObj* textureObj);

    LayerLinkList<LayerResAddTexObj> m_lists[3];  // 0x0
};
}  // namespace layer

#endif
