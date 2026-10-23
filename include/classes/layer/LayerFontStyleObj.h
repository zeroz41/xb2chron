#ifndef CLASSES_LAYER_LAYERFONTSTYLEOBJ_H
#define CLASSES_LAYER_LAYERFONTSTYLEOBJ_H

#include "layer/LayerBase.h"
#include "layer/LayerAccFontStyle.h"

namespace layer {
// table 0x7100B806A0
// A LayerBase: its table has LayerBase's shape (slot 0 destructor, slot 2 release), and the layer accessors hand
// their LayerBase* to its methods unadjusted (LayerAccFontObj::setMsg/setColorMap, LayerAccFontStyle).
class LayerFontStyleObj : public ::layer::LayerBase {
public:
    virtual ~LayerFontStyleObj();  // slot 0
    virtual void release();  // slot 2
    const char* getFontName(unsigned int style) const;
    mm::mtl::Vector<LayerStrInfo>* createColorInfo(unsigned int count);
    mm::mtl::Vector<LayerStrInfo>* createIconInfo(unsigned int count);

    // The field names follow LayerAccFontStyle's accessors that read them (not the original's).
    unsigned char pad_1C[0x4];
    const char* m_strings;  // getStyleInfo
    unsigned int m_styleDataMax;  // getStyleDataMax
    unsigned char pad_2C[0x4];
    const LayerFontStyleData* m_styleData;  // getStyleInfo
};
}  // namespace layer

#endif
