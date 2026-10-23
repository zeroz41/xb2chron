#ifndef LAYER_LAYERACCOBJBASE_H
#define LAYER_LAYERACCOBJBASE_H
#include "mm/Col4.h"

#include "mm/Col3.h"
#include "mm/Mat44.h"

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
// how an object's texture is filtered (the name is LayerAccObjBase::setTexFilterType's parameter type)
enum LayerTexFilterType {};
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
    const void* getResData() const;
    void setPos(float x, float y);
    void setRot(float rot);
    void setScale(float x, float y);
    void setMulCol(const mm::Col4& col);
    void setAddCol(const mm::Col3& col);
    void setMatrix(const mm::Mat44& mtx);
    void getPos(float& x, float& y) const;
    void getRot(float& rot) const;
    void getScale(float& x, float& y) const;
    const mm::Mat44& getMatrix() const;
    void setTexFilterType(LayerTexFilterType type);
    void setPriority(unsigned short priority);
    void setDisp(bool disp);  // the resource it was made from (a polygon object's texture)

    LayerBase* m_layer;  // the constructor's
};
}  // namespace layer

#endif
