#ifndef CLASSES_LAYER_LAYEROBJTOPLAYOUT_H
#define CLASSES_LAYER_LAYEROBJTOPLAYOUT_H

#include "classes/layer/LayerActLayout.h"

namespace layer { class LayerObjTopTexObj; }

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

    // the bits of m_renderFlags LayerObjSortLayout::finalRender tests (the name is not the original's)
    enum { RENDER_TEX_OBJ = 0xC };

    unsigned char pad_248[0x88];
    // LayerObjSortLayout::finalRender renders it first, then m_texObj when m_renderFlags holds RENDER_TEX_OBJ (the
    // field names are not the original's)
    LayerSortMan* m_sortMan;
    unsigned char pad_2D8[0xE0];
    unsigned int m_renderFlags;
    unsigned char pad_3BC[0x1C];
    LayerObjTopTexObj* m_texObj;
};
}  // namespace layer

#endif
