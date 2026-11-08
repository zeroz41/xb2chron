#ifndef LAYER_LAYERRENDERVIEW_H
#define LAYER_LAYERRENDERVIEW_H

namespace layer {
class LayerResViewPortInfo;

// the view a layer object is applied with. Only the field applyParams reads is known. 0x18 bytes:
// LayerObjManager holds one at 0x78 (its apply passes it to every object) and is 0x90 bytes (LayerManager's
// constructor allocates that).
class LayerRenderView {
public:
    unsigned char pad_0[0x8];
    // the TopTexObj/TopMemObj/TopPolyObj applyParams copy it into the object (the name and type are not the
    // original's; LayerObjUtil::calcLayerRenderView points it at its viewport, the finalRender functions set it)
    LayerResViewPortInfo* m_viewData;
    // LayerObjManager::apply zeroes it with m_viewData; its meaning is not known (the name is not the original's)
    unsigned short m_mode;  // 0x10
    unsigned char pad_12[0x6];
};
}  // namespace layer

#endif
