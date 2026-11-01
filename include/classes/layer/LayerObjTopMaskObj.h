#ifndef CLASSES_LAYER_LAYEROBJTOPMASKOBJ_H
#define CLASSES_LAYER_LAYEROBJTOPMASKOBJ_H

#include "classes/layer/LayerObj.h"
#include "grlib/CGLibDblUniformBlock.h"
#include "layer/LayerTextureObj.h"
#include "layer/LayerResViewPortInfo.h"

namespace grlib { class CGLibTextureBuffer; }
namespace layer { class LayerRenderView; }
namespace layer { class LayerResColor; }
namespace layer { class LayerResMatrix; }
namespace layer { class LayerSortMan; }

namespace layer {
// table 0x7100B800E8
class LayerObjTopMaskObj : public ::layer::LayerObj {
public:
    LayerObjTopMaskObj(const void* resource);  // LayerObjManager::createStaticMaskObj
    virtual ~LayerObjTopMaskObj();  // slot 0
    virtual void resourceInit();  // slot 3
    virtual void setDrawList(layer::LayerSortMan*, bool) {}  // slot 7
    virtual void applyParams(layer::LayerRenderView const*, layer::LayerResMatrix const&, layer::LayerResColor const&);  // slot 9
    // its first texture (LayerShdManager::setupShader binds it; the original returns a reference: the call is not a
    // tail call)
    const grlib::CGLibTextureBuffer& getTexture() const;

    // The field names follow LayerAccDefObj's accessors (its objects of type 7; not the original's).
    unsigned char pad_250[0x8];
    LayerShdViewPort m_viewPort;  // 0x258: LayerShdManager::setShaderMaskMode sets it (the name is not the original's)
    unsigned char pad_268[0x28];
    grlib::CGLibDblUniformBlock m_uniform;  // 0x290: the destructor releases it (the name is not the original's)
    LayerTextureObj* m_texture;  // resourceInit sets it up; getTexture returns its first (the name is not the original's)
    unsigned short m_iconNum;  // setIconNum / getIconNum
    unsigned short m_iconMax;  // getIconMax
};
}  // namespace layer

#endif
