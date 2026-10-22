#ifndef LAYER_LAYERACCOBJBASE_H
#define LAYER_LAYERACCOBJBASE_H

namespace layer { class LayerBase; }

namespace layer {
// where a layer object is drawn (setSpace stores it in the layer)
enum LAYER_SPACE_TYPE {};

// access to one layer object's display settings
class LayerAccObjBase {
public:
    LayerAccObjBase(LayerBase* layer);
    void setSpace(LAYER_SPACE_TYPE space);
    const void* getResData() const;  // the resource it was made from (a polygon object's texture)

    LayerBase* m_layer;  // the constructor's
};
}  // namespace layer

#endif
