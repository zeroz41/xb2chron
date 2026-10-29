#ifndef LAYER_LAYERRENDERVIEW_H
#define LAYER_LAYERRENDERVIEW_H

namespace layer {
// the view a layer object is applied with. Only the field applyParams reads is known.
class LayerRenderView {
public:
    unsigned char pad_0[0x8];
    // the TopTexObj/TopMemObj/TopPolyObj applyParams copy it into the object (the name and type are not the
    // original's)
    const void* m_viewData;
};
}  // namespace layer

#endif
