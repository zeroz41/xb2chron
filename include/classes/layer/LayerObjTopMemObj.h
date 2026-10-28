#ifndef CLASSES_LAYER_LAYEROBJTOPMEMOBJ_H
#define CLASSES_LAYER_LAYEROBJTOPMEMOBJ_H

#include "classes/layer/LayerObj.h"
#include "classes/layer/LayerObjSortMemObj.h"
#include "grlib/CGLibOneUniformBlock.h"

namespace grlib { class CGLibTextureBuffer; }
namespace layer { class LayerRenderView; }
namespace layer { class LayerResColor; }
namespace layer { class LayerResMatrix; }
namespace layer { class LayerSortMan; }

namespace layer {
// table 0x7100B7FFC8
class LayerObjTopMemObj : public ::layer::LayerObj {
public:
    virtual ~LayerObjTopMemObj();  // slot 0
    void* getBuffer();
    void updateBufer();
    void setRender(bool render);
    void setupRender();
    void lastRender();
    enum { RENDER_ON = 0x4 };  // the name is not the original's

    // The field names follow LayerAccMemObj's accessors that read them (not the original's).
    // The field names follow the functions that use them (not the original's).
    unsigned char pad_248[0x10];
    LayerObjSortMemObj m_sortObj;  // 0x258: what setDrawList puts in the sort lists
    unsigned int m_renderFlags;  // setRender sets or clears RENDER_ON
    unsigned char pad_274[0x74];
    grlib::CGLibTextureBuffer* m_texture;  // getTexture
    unsigned char pad_2F0[0x3B0];
    grlib::CGLibOneUniformBlock m_buffers[2];  // getBuffer, indexed by LayerManager::s_nDebIdx
    grlib::CGLibOneUniformBlock m_clearBuffers[2];  // updateBufer zeroes its first 16 bytes before flushing
    unsigned int m_memWidth;  // getMemWidth
    unsigned int m_memHeight;  // getMemHeight
    virtual void resourceInit();  // slot 3
    virtual void setDrawList(layer::LayerSortMan*, bool);  // slot 7
    virtual void applyParams(layer::LayerRenderView const*, layer::LayerResMatrix const&, layer::LayerResColor const&);  // slot 9
};
}  // namespace layer

#endif
