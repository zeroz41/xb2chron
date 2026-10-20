#ifndef CLASSES_LAYER_LAYEROBJTOPTEXOBJ_H
#define CLASSES_LAYER_LAYEROBJTOPTEXOBJ_H

#include "classes/layer/LayerObj.h"

namespace layer { class LayerRenderView; }
namespace layer { class LayerResColor; }
namespace layer { class LayerResMatrix; }
namespace layer { class LayerSortMan; }

namespace layer {
// table 0x7100B80028
class LayerObjTopTexObj : public ::layer::LayerObj {
public:
    virtual ~LayerObjTopTexObj();  // slot 0
    virtual void setDrawList(layer::LayerSortMan*, bool);  // slot 7
    virtual void applyParams(layer::LayerRenderView const*, layer::LayerResMatrix const&, layer::LayerResColor const&);  // slot 9
};
}  // namespace layer

#endif
