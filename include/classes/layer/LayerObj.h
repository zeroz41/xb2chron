#ifndef CLASSES_LAYER_LAYEROBJ_H
#define CLASSES_LAYER_LAYEROBJ_H

#include "layer/LayerBase.h"
#include "layer/LayerAccObjBase.h"
#include "mm/Col3.h"
#include "mm/Col4.h"
#include "mm/Mat44.h"

namespace layer { class LayerRenderView; }
namespace layer { class LayerResColor; }
namespace layer { class LayerResMatrix; }
namespace layer { class LayerResUpdateInfo; }
namespace layer { class LayerSortMan; }

namespace layer {
// table 0x7100B7F9E8
class LayerObj : public ::layer::LayerBase {
public:
    virtual ~LayerObj();  // slot 0
    virtual void release();  // slot 2
    virtual void resourceInit() {}  // slot 3
    virtual void apply(layer::LayerSortMan*, layer::LayerRenderView const*);  // slot 4
    virtual void applyBegin(layer::LayerResUpdateInfo&, layer::LayerRenderView const*);  // slot 5
    virtual void applyEnd(layer::LayerResUpdateInfo&, layer::LayerRenderView const*);  // slot 6
    virtual void setDrawList(layer::LayerSortMan*, bool) = 0;  // slot 7
    virtual void applyPartsSetup() {}  // slot 8
    virtual void applyParams(layer::LayerRenderView const*, layer::LayerResMatrix const&, layer::LayerResColor const&) {}  // slot 9

    void setPos(float x, float y);
    void setRot(float rot);
    void setScale(float x, float y);
    void setMulCol(const mm::Col4& col);
    void setAddCol(const mm::Col3& col);
    void setMatrix(const mm::Mat44& mtx);
    void getPos(float& x, float& y) const;
    void getRot(float& rot) const;
    void getScale(float& x, float& y) const;
    const mm::Col4& getMulCol() const;
    const mm::Mat44& getMatrix() const;
    void setDisp(bool disp);
    void setFlip(LayerFlipType type, bool flip);

    // The field names follow LayerAccObjBase's accessors that read and write them (not the original's).
    unsigned char pad_1C[0x9C];
    const void* m_resData;  // getResData
    unsigned short m_priority;  // setPriority
    unsigned char pad_C2[0x1];
    unsigned char m_space;  // setSpace (a LAYER_SPACE_TYPE)
    unsigned char m_blendType;  // setBlendType (a LayerBlendType)
    unsigned char pad_C5[0x1];
    unsigned char m_texFilterType;  // setTexFilterType (a LayerTexFilterType)
    unsigned char pad_C7[0xCD];
    unsigned short m_pixelWidth;  // getPixelWidth
    unsigned short m_pixelHeight;  // getPixelHeight
    unsigned char m_centerType;  // set/getCenterType (a LayerCenterType)
    unsigned char pad_199[0xA7];
    const LayerBase* m_maskObj;  // setMaskObj
};
}  // namespace layer

#endif
