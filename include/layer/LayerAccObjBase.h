#ifndef LAYER_LAYERACCOBJBASE_H
#define LAYER_LAYERACCOBJBASE_H
#include "mm/Col4.h"

namespace layer { class LayerBase; }

namespace layer {
// where a layer object is drawn (setSpace stores it in the layer)
enum LAYER_SPACE_TYPE {};
// which way an object is mirrored (UIImageObject::setHFlip passes 0, setVFlip 1)
enum LayerFlipType {};

// how an object is blended (UIObject::setBlendType maps its blend type through a table)
enum LayerBlendType {};
// where an object is anchored (UIObject::apply maps its display mode through a table)
enum LayerCenterType {};
// access to one layer object's display settings
class LayerAccObjBase {
public:
    LayerAccObjBase(LayerBase* layer);
    void setSpace(LAYER_SPACE_TYPE space);
    void setBlendType(LayerBlendType type);
    void setCenterType(LayerCenterType type);
    LayerCenterType getCenterType() const;
    unsigned short getPixelWidth() const;
    unsigned short getPixelHeight() const;
    const mm::Col4& getMulCol() const;
    void setFlip(LayerFlipType type, bool flip);
    void setMaskObj(const LayerBase* mask);  // the mask object that masks it
    const void* getResData() const;  // the resource it was made from (a polygon object's texture)

    LayerBase* m_layer;  // the constructor's
};
}  // namespace layer

#endif
