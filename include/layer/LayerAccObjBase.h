#ifndef LAYER_LAYERACCOBJBASE_H
#define LAYER_LAYERACCOBJBASE_H

namespace layer { class LayerBase; }

namespace layer {
// where a layer object is drawn (setSpace stores it in the layer)
enum LAYER_SPACE_TYPE {};
// which way an object is mirrored (UIImageObject::setHFlip passes 0, setVFlip 1)
enum LayerFlipType {};

// access to one layer object's display settings
class LayerAccObjBase {
public:
    LayerAccObjBase(LayerBase* layer);
    void setSpace(LAYER_SPACE_TYPE space);
    void setFlip(LayerFlipType type, bool flip);
    void setMaskObj(const LayerBase* mask);  // the mask object that masks it
    const void* getResData() const;  // the resource it was made from (a polygon object's texture)

    LayerBase* m_layer;  // the constructor's
};
}  // namespace layer

#endif
