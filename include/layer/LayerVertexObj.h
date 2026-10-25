#ifndef LAYER_LAYERVERTEXOBJ_H
#define LAYER_LAYERVERTEXOBJ_H

namespace layer {
// a layer object's vertex buffers (layer/LayerSortMan)
class LayerVertexObj {
public:
    // binds the vertex buffer of the index (layer::LayerShdManager::setupVertex)
    void setVertex(unsigned int index);
};
}  // namespace layer

#endif
