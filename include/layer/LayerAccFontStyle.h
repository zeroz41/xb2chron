#ifndef LAYER_LAYERACCFONTSTYLE_H
#define LAYER_LAYERACCFONTSTYLE_H

namespace layer { class LayerStrInfo; }
#include "mm/mtl/Vector.h"

namespace layer { class LayerBase; }

namespace layer {
// a style's record in a font style object's table (0x28 bytes; the type's name is the original's, from
// LayerFontDrawBuffer's constructor's signature; the field names are not the original's)
struct LyrFontStyleData {
    unsigned char pad_0[0x8];
    unsigned int m_fontName;  // its font's name, at this offset in the object's strings (getFontName)
    float m_offsetX;  // UIFontManager::getFontStyleInfo copies it beside m_offsetY (inferred from that pairing)
    float m_offsetY;  // UIFontManager::StyleInfo's m_offsetY
    unsigned char pad_14[0x14];
};
// what getStyleInfo hands back: the object's strings and the style's record (the names are not the original's)
struct LayerFontStyleInfo {
    const char* m_strings;
    const LyrFontStyleData* m_data;  // the first record for a style past the last
};
// access to a font style layer object (LayerAccManager::createFontStyleObj's)
class LayerAccFontStyle {
public:
    LayerAccFontStyle(LayerBase* layer);
    const char* getFontName(unsigned int style) const;
    unsigned int getStyleDataMax() const;  // the number of styles
    LayerFontStyleInfo getStyleInfo(unsigned int style) const;
    // a new list of count colours (icons), replacing the object's
    mm::mtl::Vector<LayerStrInfo>* createColorInfo(unsigned int count);
    mm::mtl::Vector<LayerStrInfo>* createIconInfo(unsigned int count);
    LayerBase* m_layer;  // the constructor's
};
}  // namespace layer

#endif
