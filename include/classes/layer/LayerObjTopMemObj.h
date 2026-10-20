#ifndef CLASSES_LAYER_LAYEROBJTOPMEMOBJ_H
#define CLASSES_LAYER_LAYEROBJTOPMEMOBJ_H

#include "classes/layer/LayerObj.h"

namespace layer { class LayerRenderView; }
namespace layer { class LayerResColor; }
namespace layer { class LayerResMatrix; }
namespace layer { class LayerSortMan; }

namespace layer {
// table 0x7100B7FFC8
class LayerObjTopMemObj : public ::layer::LayerObj {
public:
    virtual ~LayerObjTopMemObj();  // slot 0
    virtual void resourceInit();  // slot 3
    virtual void setDrawList(layer::LayerSortMan*, bool);  // slot 7
    virtual void applyParams(layer::LayerRenderView const*, layer::LayerResMatrix const&, layer::LayerResColor const&);  // slot 9
};
}  // namespace layer

#endif
