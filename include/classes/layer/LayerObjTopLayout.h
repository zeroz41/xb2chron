#ifndef CLASSES_LAYER_LAYEROBJTOPLAYOUT_H
#define CLASSES_LAYER_LAYEROBJTOPLAYOUT_H

#include "classes/layer/LayerActLayout.h"
#include "classes/layer/LayerObjSortLayout.h"
#include "layer/LayerResViewPortInfo.h"
#include "layer/LayerViewPort.h"
#include "mm/Col4.h"

namespace layer { class LayerObjTopTexObj; }

namespace layer { class LayerRenderView; }
namespace layer { class LayerResUpdateInfo; }
namespace layer { class LayerSortMan; }

namespace layer {
// table 0x7100B7FF60
class LayerObjTopLayout : public ::layer::LayerActLayout {
public:
    // inline: LayerObjManager::createStaticLayoutObj builds it (a layout object, m_objType 3, displayed)
    LayerObjTopLayout() : m_sortObj(this) {
        m_objType = 3;
        m_stateFlags |= STATE_DISP;
    }
    virtual ~LayerObjTopLayout();  // slot 0
    virtual void apply(layer::LayerSortMan*, layer::LayerRenderView const*);  // slot 4
    virtual void applyBegin(layer::LayerResUpdateInfo&, layer::LayerRenderView const*);  // slot 5
    virtual void applyEnd(layer::LayerResUpdateInfo&, layer::LayerRenderView const*);  // slot 6
    virtual void setDrawList(layer::LayerSortMan*, bool);  // slot 7
    // creates the objects of a layout binary's positions that have one, and resets the render info
    void workLayoutCreate(const void* resource);
    void updateDispOffLayout(LayerResUpdateInfo& info, const LayerRenderView* view);
    void updateEndLayout(const LayerRenderView* view, LayerResUpdateInfo& info);

    // the bits of m_renderFlags LayerObjSortLayout::finalRender tests (the name is not the original's)
    enum { RENDER_TEX_OBJ = 0xC };
    // updateEndLayout: the children are rendered into m_renderTarget through m_texViewPort and m_texObj shows them
    // (the name is not the original's)
    enum { RENDER_TEXTURE = 0x4 };

    unsigned char pad_2C8[0x8];
    // LayerObjSortLayout::finalRender renders it first, then m_texObj when m_renderFlags holds RENDER_TEX_OBJ (the
    // field names are not the original's)
    LayerSortMan* m_sortMan;
    // 0x2D8: updateEndLayout sets it up with LayerObjUtil::calcLayerRenderView (the name is not the original's)
    LayerResViewPortInfo m_viewPortInfo;
    unsigned char pad_310[0xA8];
    unsigned int m_renderFlags;
    // 0x3BC..0x3F0: the texture target updateEndLayout renders the children into while m_renderFlags holds 0x4
    // (the field names are not the original's)
    LayerViewPort m_texViewPort;
    grlib::CGLibRenderTarget* m_renderTarget;
    LayerObjTopTexObj* m_texObj;
    mm::Col4 m_clearColor;
    // 0x3F0: the uniform block calcLayerRenderView sets; updateEndLayout keeps last frame's in m_oldUniform and
    // deletes it a frame later (the names are not the original's)
    grlib::CGLibDblUniformBlock* m_uniform;
    grlib::CGLibDblUniformBlock* m_oldUniform;
    LayerObjSortLayout m_sortObj;  // 0x400: what setDrawList puts in the sort lists (the name is not the original's)
};
}  // namespace layer

#endif
