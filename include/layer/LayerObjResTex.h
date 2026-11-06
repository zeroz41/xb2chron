#ifndef LAYER_LAYEROBJRESTEX_H
#define LAYER_LAYEROBJRESTEX_H

#include "layer/LayerLinkList.h"
#include "layer/LayerResAddTexObj.h"

namespace grlib { class CGLibTextureBuffer; }

namespace layer {
class LayerTextureObj;

// the added textures of a LayerObjTopDef (0x2C0) or LayerObjTopPolyObj (0x2B8): 0x48 bytes, the next field of
// both follows it. clear() deletes the objects of its three lists (0x0, 0x18, 0x30). setAddTexture marks the
// m_list objects of the same index with the bit of LayerManager::s_nStkIdx and adds the new object to
// m_addLists[s_nStkIdx] (the names are not the original's).
class LayerObjResTex {
public:
    void setAddTexture(const void* res, unsigned int index);
    void setAddTexture(grlib::CGLibTextureBuffer& texture, unsigned int index);
    void clear();
    // true when the textures changed (LayerObjTopDef::updateFast then re-tests the first one's format)
    bool updateTexutre(grlib::CGLibTextureBuffer** textures, LayerTextureObj* textureObj);

    LayerLinkList<LayerResAddTexObj> m_list;          // 0x0
    LayerLinkList<LayerResAddTexObj> m_addLists[2];  // 0x18: by LayerManager::s_nStkIdx
};
}  // namespace layer

#endif
