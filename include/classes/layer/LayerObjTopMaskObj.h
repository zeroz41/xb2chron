// not proven yet: its table differs from the original's (word 4: _ZN5layer12LayerObjUtil7releaseEv where the original has _ZN5layer8LayerObj7releaseEv)
#ifndef CLASSES_LAYER_LAYEROBJTOPMASKOBJ_H
#define CLASSES_LAYER_LAYEROBJTOPMASKOBJ_H

#include "classes/layer/LayerObjUtil.h"

namespace layer { class LayerRenderView; }
namespace layer { class LayerResColor; }
namespace layer { class LayerResMatrix; }
namespace layer { class LayerSortMan; }

namespace layer {
// table 0x7100B800E8
class LayerObjTopMaskObj : public ::layer::LayerObjUtil {
public:
    virtual ~LayerObjTopMaskObj();  // slot 0
    virtual void resourceInit();  // slot 3
    virtual void setDrawList(layer::LayerSortMan*, bool);  // slot 7
    virtual void applyParams(layer::LayerRenderView const*, layer::LayerResMatrix const&, layer::LayerResColor const&);  // slot 9
};
}  // namespace layer

#endif
