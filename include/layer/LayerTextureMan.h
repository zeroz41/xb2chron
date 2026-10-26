#ifndef LAYER_LAYERTEXTUREMAN_H
#define LAYER_LAYERTEXTUREMAN_H

#include "layer/LayerLinkList.h"
#include "layer/LayerTextureObj.h"

namespace layer {
class LayerManager;

// the shared texture objects (LayerShdManager::m_textureMan): one per resource, counted
class LayerTextureMan : public LayerLinkList<LayerTextureObj> {
public:
    LayerTextureMan(LayerManager* manager);
    ~LayerTextureMan();
    // the resource's texture object: a new one, or the existing one with a user more
    LayerTextureObj* createTextureObj(const unsigned char* res);
    // one user fewer: the last deletes it
    void releaseTextureObj(LayerTextureObj* obj);

    LayerManager* m_manager;  // 0x18
};
}  // namespace layer

#endif
