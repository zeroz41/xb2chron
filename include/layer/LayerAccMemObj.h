#ifndef LAYER_LAYERACCMEMOBJ_H
#define LAYER_LAYERACCMEMOBJ_H

namespace layer { class LayerBase; }
namespace layer { class LayerObjTopMemObj; }
namespace grlib { class CGLibTextureBuffer; }

namespace layer {
// access to a memory layer object (a LayerObjTopMemObj: getMemBufer asks it for its buffer)
class LayerAccMemObj {
public:
    LayerAccMemObj(LayerBase* layer);
    void* getMemBufer();     // its buffer (LayerObjTopMemObj::getBuffer)
    void updateMemBufer();
    void setRender(bool render);
    // the texture it draws into: the pointer at the object's 0x2E8 (the type is not in the symbol)
    grlib::CGLibTextureBuffer* getTexture();

    LayerBase* m_layer;              // the constructor's
    LayerObjTopMemObj* m_memObj;     // the constructor's layer again, as the memory object it is
};
}  // namespace layer

#endif
