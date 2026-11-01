#ifndef CLASSES_LAYER_LAYEROBJTOPMEMOBJ_H
#define CLASSES_LAYER_LAYEROBJTOPMEMOBJ_H

#include "classes/layer/LayerObj.h"
#include "layer/LayerAccLayoutObj.h"
#include "grlib/CGLibDblUniformBlock.h"
#include "classes/layer/LayerObjSortMemObj.h"
#include "grlib/CGLibOneUniformBlock.h"
#include "grlib/CGLibRenderTarget.h"

namespace grlib { class CGLibTextureBuffer; }
namespace layer { class LayerRenderView; }
namespace layer { class LayerResColor; }
namespace layer { class LayerResMatrix; }
namespace layer { class LayerSortMan; }

namespace layer {
// table 0x7100B7FFC8
class LayerObjTopMemObj : public ::layer::LayerObj {
public:
    LayerObjTopMemObj(unsigned int width, unsigned int height, LayerMemType type);  // LayerObjManager::createStaticMemObj
    virtual ~LayerObjTopMemObj();  // slot 0
    void* getBuffer();
    void updateBufer();
    void setRender(bool render);
    void setupRender();
    void lastRender();
    enum { RENDER_ON = 0x4 };  // the name is not the original's

    // The field names follow LayerAccMemObj's accessors that read them (not the original's).
    // The field names follow the functions that use them (not the original's).
    const void* m_viewData;  // applyParams copies LayerRenderView::m_viewData (the name is not the original's)
    LayerObjSortMemObj m_sortObj;  // 0x258: what setDrawList puts in the sort lists
    unsigned int m_renderFlags;  // setRender sets or clears RENDER_ON
    unsigned char pad_274[0x4];
    // 0x278: LayerAccMemObj::getTexture returns its m_pTexture (0x2E8); the destructor releases it
    grlib::CGLibRenderTarget m_renderTarget;
    grlib::CGLibDblUniformBlock m_uniform;  // 0x640: applyParams updates it (the name is not the original's)
    grlib::CGLibOneUniformBlock m_oneUniform;  // 0x678: the destructor releases it first of the five
    grlib::CGLibOneUniformBlock m_buffers[2];  // getBuffer, indexed by LayerManager::s_nDebIdx
    grlib::CGLibOneUniformBlock m_clearBuffers[2];  // updateBufer zeroes its first 16 bytes before flushing
    unsigned int m_memWidth;  // getMemWidth
    unsigned int m_memHeight;  // getMemHeight
    unsigned char pad_748[0x18];  // createStaticMemObj allocates 0x760
    virtual void resourceInit();  // slot 3
    virtual void setDrawList(layer::LayerSortMan*, bool);  // slot 7
    virtual void applyParams(layer::LayerRenderView const*, layer::LayerResMatrix const&, layer::LayerResColor const&);  // slot 9
};
}  // namespace layer

#endif
