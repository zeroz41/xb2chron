#ifndef LAYER_LAYERRENDERVIEW_H
#define LAYER_LAYERRENDERVIEW_H

namespace layer {
// the view a layer object is applied with. Only the field applyParams reads is known. 0x18 bytes:
// LayerObjManager holds one at 0x78 (its apply passes it to every object) and is 0x90 bytes (LayerManager's
// constructor allocates that).
class LayerRenderView {
public:
    unsigned char pad_0[0x8];
    // the TopTexObj/TopMemObj/TopPolyObj applyParams copy it into the object (the name and type are not the
    // original's)
    const void* m_viewData;
    // LayerObjManager::apply zeroes the halfword at 0x10 with m_viewData; its meaning is not known
    unsigned char pad_10[0x8];
};
}  // namespace layer

#endif
