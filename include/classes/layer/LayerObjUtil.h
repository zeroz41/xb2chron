#ifndef CLASSES_LAYER_LAYEROBJUTIL_H
#define CLASSES_LAYER_LAYEROBJUTIL_H

namespace layer { class LayerBasePos; }
namespace layer { class LayerCenterType; }
namespace layer { class LayerRenderView; }
namespace layer { class LayerResColor; }
namespace layer { class LayerResMatrix; }
namespace layer { class LayerResRenderInfo; }
namespace layer { class LayerResUpdateInfo; }
namespace layer { class LayerSortMan; }
namespace layer { class LyrLayoutPosData; }

namespace layer {
// table none (its derived classes')
class LayerObjUtil {
public:
    virtual ~LayerObjUtil();  // slot 0
    virtual void release();  // slot 2
    virtual void resourceInit() = 0;  // slot 3
    virtual void apply(layer::LayerSortMan*, layer::LayerRenderView const*);  // slot 4
    virtual void applyBegin(layer::LayerResUpdateInfo&, layer::LayerRenderView const*);  // slot 5
    virtual void applyEnd(layer::LayerResUpdateInfo&, layer::LayerRenderView const*);  // slot 6
    virtual void setDrawList(layer::LayerSortMan*, bool) = 0;  // slot 7
    virtual void applyPartsSetup();  // slot 8
    virtual void applyParams(layer::LayerRenderView const*, layer::LayerResMatrix const&, layer::LayerResColor const&) = 0;  // slot 9
    virtual void calcScl_Pixel_Up(float*, layer::LayerBasePos const&, layer::LayerResRenderInfo const&);  // slot 10
    virtual void calcScl_Correction_Up(float*, layer::LayerBasePos const&, layer::LayerResRenderInfo const&);  // slot 11
    virtual void calcPos_Pixel_Up(float*, layer::LayerBasePos const&);  // slot 12
    virtual void calcPos_Correction_Up(float*, layer::LayerBasePos const&);  // slot 13
    virtual void calcMdlPos_Center_Up(float*, float*, float const*, layer::LayerBasePos const&);  // slot 14
    virtual void calcMdlPos_Center_Down(float*, float*, float const*, layer::LayerBasePos const&);  // slot 15
    virtual void calcMdlPos_Center_Center(float*, float*, float const*, layer::LayerBasePos const&);  // slot 16
    virtual void calcSwfScl_Pixel_Up(float*, layer::LayerBasePos const&, layer::LayerResRenderInfo const&);  // slot 17
    virtual void calcSwfScl_Correction_Up(float*, layer::LayerBasePos const&, layer::LayerResRenderInfo const&);  // slot 18
    virtual void calcPosData_Pixel_Up(float*, layer::LyrLayoutPosData const*, layer::LayerCenterType, float, float);  // slot 19
    virtual void calcPosData_Correction_Up(float*, layer::LyrLayoutPosData const*, layer::LayerCenterType, float, float);  // slot 20
};
}  // namespace layer

#endif
