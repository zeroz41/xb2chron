#ifndef CLASSES_LAYER_LAYEROBJTOPTEXOBJ_H
#define CLASSES_LAYER_LAYEROBJTOPTEXOBJ_H

#include "classes/layer/LayerObj.h"
#include "grlib/CGLibDblUniformBlock.h"
#include "classes/layer/LayerObjSortTexObj.h"

namespace layer { class LayerRenderView; }
namespace layer { class LayerResColor; }
namespace layer { class LayerResMatrix; }
namespace layer { class LayerSortMan; }

namespace layer {
// table 0x7100B80028
class LayerObjTopTexObj : public ::layer::LayerObj {
public:
    virtual ~LayerObjTopTexObj();  // slot 0
    void finalRender();
    virtual void setDrawList(layer::LayerSortMan*, bool);  // slot 7
    virtual void applyParams(layer::LayerRenderView const*, layer::LayerResMatrix const&, layer::LayerResColor const&);  // slot 9

    unsigned char pad_248[0x10];
    LayerObjSortTexObj m_sortObj;  // 0x258: what setDrawList puts in the sort lists (the name is not the original's)
    unsigned char pad_270[0x8];
    grlib::CGLibDblUniformBlock m_uniform;  // 0x278: the destructor releases it (the name is not the original's)
};
}  // namespace layer

#endif
