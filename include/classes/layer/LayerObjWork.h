// not proven yet: its table differs from the original's (word 4: _ZN5layer12LayerObjWork7releaseEv where the original has _ZN5layer8LayerObj7releaseEv)
#ifndef CLASSES_LAYER_LAYEROBJWORK_H
#define CLASSES_LAYER_LAYEROBJWORK_H

namespace layer { class LayerRenderView; }
namespace layer { class LayerResColor; }
namespace layer { class LayerResMatrix; }
namespace layer { class LayerResUpdateInfo; }
namespace layer { class LayerSortMan; }
namespace layer { class LyrActionData; }

namespace layer {
// table 0x7100B801A0
class LayerObjWork {
public:
    virtual ~LayerObjWork();  // slot 0
    virtual void release();  // slot 2
    virtual void resourceInit();  // slot 3
    virtual void apply(layer::LayerSortMan*, layer::LayerRenderView const*);  // slot 4
    virtual void applyBegin(layer::LayerResUpdateInfo&, layer::LayerRenderView const*);  // slot 5
    virtual void applyEnd(layer::LayerResUpdateInfo&, layer::LayerRenderView const*);  // slot 6
    virtual void vf7() = 0;  // slot 7
    virtual void applyPartsSetup();  // slot 8
    virtual void applyParams(layer::LayerRenderView const*, layer::LayerResMatrix const&, layer::LayerResColor const&);  // slot 9
    virtual void updatePartsAction(layer::LyrActionData const*);  // slot 10
};
}  // namespace layer

#endif
