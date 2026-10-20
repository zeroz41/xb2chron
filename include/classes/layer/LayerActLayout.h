#ifndef CLASSES_LAYER_LAYERACTLAYOUT_H
#define CLASSES_LAYER_LAYERACTLAYOUT_H

namespace layer { class LayerRenderView; }
namespace layer { class LayerResColor; }
namespace layer { class LayerResMatrix; }
namespace layer { class LayerResUpdateInfo; }
namespace layer { class LayerSortMan; }
namespace layer { class LyrActionData; }

namespace layer {
// table none (its derived classes')
class LayerActLayout {
public:
    virtual ~LayerActLayout();  // slot 0
    virtual void release();  // slot 2
    virtual void resourceInit();  // slot 3
    virtual void apply(layer::LayerSortMan*, layer::LayerRenderView const*) = 0;  // slot 4
    virtual void applyBegin(layer::LayerResUpdateInfo&, layer::LayerRenderView const*) = 0;  // slot 5
    virtual void applyEnd(layer::LayerResUpdateInfo&, layer::LayerRenderView const*) = 0;  // slot 6
    virtual void setDrawList(layer::LayerSortMan*, bool) = 0;  // slot 7
    virtual void applyPartsSetup();  // slot 8
    virtual void applyParams(layer::LayerRenderView const*, layer::LayerResMatrix const&, layer::LayerResColor const&);  // slot 9
    virtual void updatePartsAction(layer::LyrActionData const*);  // slot 10
};
}  // namespace layer

#endif
