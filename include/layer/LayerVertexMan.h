#ifndef LAYER_LAYERVERTEXMAN_H
#define LAYER_LAYERVERTEXMAN_H

#include "layer/LayerLinkList.h"
#include "layer/LayerVertexObj.h"

namespace layer {
class LayerManager;

// the shared vertex objects (LayerShdManager::m_vertexMan): one per resource, counted
class LayerVertexMan : public LayerLinkList<LayerVertexObj> {
public:
    LayerVertexMan(LayerManager* manager);
    ~LayerVertexMan();
    // the resource's vertex object: a new one, or the existing one with a user more
    LayerVertexObj* createVertexObj(const unsigned char* res);
    // one user fewer: the last deletes it (inline in LayerVertexObj::release)
    void releaseVertexObj(LayerVertexObj* obj) {
        if (obj->subRef()) {
            removeList(obj);
            obj->vertexRelease();
            delete obj;
        }
    }

    LayerManager* m_manager;  // 0x18
};
}  // namespace layer

#endif
