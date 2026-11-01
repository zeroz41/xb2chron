#ifndef LAYER_LAYERRESVIEWPORTINFO_H
#define LAYER_LAYERRESVIEWPORTINFO_H

#include "mm/Col4.h"

namespace grlib { class CGLibDblUniformBlock; class CGLibRenderTarget; }

namespace layer {
// a viewport rectangle in layout units (LayerShdManager keeps the one it set; LayerResViewPortInfo and
// LayerObjTopMaskObj hold one; the names are not the original's)
struct LayerShdViewPort {
    float m_x;
    float m_y;
    float m_width;
    float m_height;
};

// what LayerShdManager::setViewPort sets up: a rectangle, or a render target drawn to (cleared once); the field names
// are not the original's
class LayerResViewPortInfo {
public:
    LayerShdViewPort m_viewPort;  // 0x00, used without a render target
    grlib::CGLibRenderTarget* m_pRenderTarget;  // 0x10
    grlib::CGLibDblUniformBlock* m_pUniform;  // 0x18, becomes LayerShdManager::m_pMaskWork
    mm::Col4 m_clearColor;  // 0x20, the render target's clear colour
    unsigned int m_flags;   // 0x30: 1 = the render target was cleared
};
}  // namespace layer

#endif
