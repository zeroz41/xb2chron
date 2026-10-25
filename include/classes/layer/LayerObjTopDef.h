#ifndef CLASSES_LAYER_LAYEROBJTOPDEF_H
#define CLASSES_LAYER_LAYEROBJTOPDEF_H

#include "classes/layer/LayerObjMesh.h"

namespace layer { class LayerRenderView; }
namespace layer { class LayerResUpdateInfo; }
namespace layer { class LayerSortMan; }

namespace layer {
// table 0x7100B7FE98
class LayerObjTopDef : public ::layer::LayerObjMesh {
public:
    virtual ~LayerObjTopDef();  // slot 0
    void finalRender();
    virtual void resourceInit();  // slot 3
    virtual void apply(layer::LayerSortMan*, layer::LayerRenderView const*);  // slot 4
    virtual void applyBegin(layer::LayerResUpdateInfo&, layer::LayerRenderView const*);  // slot 5
    virtual void applyEnd(layer::LayerResUpdateInfo&, layer::LayerRenderView const*);  // slot 6
    virtual void setDrawList(layer::LayerSortMan*, bool);  // slot 7
};
}  // namespace layer

#endif
