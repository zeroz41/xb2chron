#ifndef CLASSES_LAYER_LAYEROBJTOPMEMOBJ_H
#define CLASSES_LAYER_LAYEROBJTOPMEMOBJ_H

#include "classes/layer/LayerObj.h"

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

    // The field names follow LayerAccMemObj's accessors that read them (not the original's).
    unsigned char pad_248[0xA0];
    grlib::CGLibTextureBuffer* m_texture;  // getTexture
    unsigned char pad_2F0[0x450];
    unsigned int m_memWidth;  // getMemWidth
    unsigned int m_memHeight;  // getMemHeight
    virtual void resourceInit();  // slot 3
    virtual void setDrawList(layer::LayerSortMan*, bool);  // slot 7
    virtual void applyParams(layer::LayerRenderView const*, layer::LayerResMatrix const&, layer::LayerResColor const&);  // slot 9
};
}  // namespace layer

#endif
