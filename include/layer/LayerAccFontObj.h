#ifndef LAYER_LAYERACCFONTOBJ_H
#define LAYER_LAYERACCFONTOBJ_H

namespace layer { class LayerBase; }

namespace layer {
// how a font object lays out its text (setDispSetting stores it in the layer object)
enum LayerFontSetting {};

// access to a font layer object
class LayerAccFontObj {
public:
    LayerAccFontObj(LayerBase* layer);
    void setDispSetting(LayerFontSetting setting);

    LayerBase* m_layer;  // the constructor's
};
}  // namespace layer

#endif
