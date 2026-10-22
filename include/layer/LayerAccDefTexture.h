#ifndef LAYER_LAYERACCDEFTEXTURE_H
#define LAYER_LAYERACCDEFTEXTURE_H

namespace layer { class LayerBase; }

namespace layer {
// access to a default layer object's texture (UIImageObject::changeBin swaps it)
class LayerAccDefTexture {
public:
    LayerAccDefTexture(LayerBase* layer);
    void setTexutre(const void* texture);

    LayerBase* m_layer;  // the constructor's
};
}  // namespace layer

#endif
