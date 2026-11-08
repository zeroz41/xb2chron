#ifndef CLASSES_LAYER_LAYEROBJTOPTEXOBJ_H
#define CLASSES_LAYER_LAYEROBJTOPTEXOBJ_H

#include "classes/layer/LayerObj.h"
#include "grlib/CGLibDblUniformBlock.h"
#include "classes/layer/LayerObjSortTexObj.h"

namespace layer { class LayerRenderView; }
namespace layer { class LayerResViewPortInfo; }
namespace layer { class LayerResColor; }
namespace layer { class LayerResMatrix; }
namespace layer { class LayerSortMan; }

namespace layer {
// table 0x7100B80028
class LayerObjTopTexObj : public ::layer::LayerObj {
public:
    LayerObjTopTexObj(const grlib::CGLibTextureBuffer* texture);  // LayerObjManager::createStaticTexObj
    virtual ~LayerObjTopTexObj();  // slot 0
    void finalRender();
    virtual void setDrawList(layer::LayerSortMan*, bool);  // slot 7
    virtual void applyParams(layer::LayerRenderView const*, layer::LayerResMatrix const&, layer::LayerResColor const&);  // slot 9

    // applyParams copies LayerRenderView::m_viewData; finalRender sets it as the viewport (the name is not the
    // original's)
    LayerResViewPortInfo* m_viewData;
    LayerObjSortTexObj m_sortObj;  // 0x258: what setDrawList puts in the sort lists (the name is not the original's)
    const grlib::CGLibTextureBuffer* m_texture;  // 0x270: finalRender draws it (the name is not the original's)
    grlib::CGLibDblUniformBlock m_uniform;  // 0x278: the destructor releases it (the name is not the original's)
};
}  // namespace layer

#endif
