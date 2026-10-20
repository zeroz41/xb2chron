// not proven yet: its table differs from the original's (word 4: _ZN5layer15LayerObjTopFont7releaseEv where the original has _ZN5layer8LayerObj7releaseEv)
#ifndef CLASSES_LAYER_LAYEROBJTOPFONT_H
#define CLASSES_LAYER_LAYEROBJTOPFONT_H

namespace layer { class LayerRenderView; }
namespace layer { class LayerResColor; }
namespace layer { class LayerResMatrix; }
namespace layer { class LayerResUpdateInfo; }
namespace layer { class LayerSortMan; }

namespace layer {
// table 0x7100B7FF00
class LayerObjTopFont {
public:
    virtual ~LayerObjTopFont();  // slot 0
    virtual void release();  // slot 2
    virtual void resourceInit();  // slot 3
    virtual void apply(layer::LayerSortMan*, layer::LayerRenderView const*);  // slot 4
    virtual void applyBegin(layer::LayerResUpdateInfo&, layer::LayerRenderView const*);  // slot 5
    virtual void applyEnd(layer::LayerResUpdateInfo&, layer::LayerRenderView const*);  // slot 6
    virtual void setDrawList(layer::LayerSortMan*, bool);  // slot 7
    virtual void applyPartsSetup();  // slot 8
    virtual void applyParams(layer::LayerRenderView const*, layer::LayerResMatrix const&, layer::LayerResColor const&);  // slot 9
};
}  // namespace layer

#endif
