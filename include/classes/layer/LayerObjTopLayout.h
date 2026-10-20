// not proven yet: its table differs from the original's (word 4: _ZN5layer14LayerActLayout7releaseEv where the original has _ZN5layer8LayerObj7releaseEv)
#ifndef CLASSES_LAYER_LAYEROBJTOPLAYOUT_H
#define CLASSES_LAYER_LAYEROBJTOPLAYOUT_H

#include "classes/layer/LayerActLayout.h"

namespace layer { class LayerRenderView; }
namespace layer { class LayerResUpdateInfo; }
namespace layer { class LayerSortMan; }

namespace layer {
// table 0x7100B7FF60
class LayerObjTopLayout : public ::layer::LayerActLayout {
public:
    virtual ~LayerObjTopLayout();  // slot 0
    virtual void apply(layer::LayerSortMan*, layer::LayerRenderView const*);  // slot 4
    virtual void applyBegin(layer::LayerResUpdateInfo&, layer::LayerRenderView const*);  // slot 5
    virtual void applyEnd(layer::LayerResUpdateInfo&, layer::LayerRenderView const*);  // slot 6
    virtual void setDrawList(layer::LayerSortMan*, bool);  // slot 7
};
}  // namespace layer

#endif
