// not proven yet: its table differs from the original's (word 12: _ZN5layer8LayerObj9actend_noEPKNS_13LyrActionDataEb where the original has _ZN5layer12LayerActBase9actend_noEPKNS_13LyrActionDataEb)
#ifndef CLASSES_LAYER_LAYEROBJ_H
#define CLASSES_LAYER_LAYEROBJ_H

namespace layer { class LayerRenderView; }
namespace layer { class LayerResColor; }
namespace layer { class LayerResMatrix; }
namespace layer { class LayerResUpdateInfo; }
namespace layer { class LayerSortMan; }
namespace layer { class LyrActionData; }

namespace layer {
// table 0x7100B7F9E8
class LayerObj {
public:
    virtual ~LayerObj();  // slot 0
    virtual void release();  // slot 2
    virtual void resourceInit();  // slot 3
    virtual void apply(layer::LayerSortMan*, layer::LayerRenderView const*);  // slot 4
    virtual void applyBegin(layer::LayerResUpdateInfo&, layer::LayerRenderView const*);  // slot 5
    virtual void applyEnd(layer::LayerResUpdateInfo&, layer::LayerRenderView const*);  // slot 6
    virtual void vf7() = 0;  // slot 7
    virtual void applyPartsSetup();  // slot 8
    virtual void applyParams(layer::LayerRenderView const*, layer::LayerResMatrix const&, layer::LayerResColor const&);  // slot 9
    virtual void actend_no(layer::LyrActionData const*, bool);  // slot 10
};
}  // namespace layer

#endif
