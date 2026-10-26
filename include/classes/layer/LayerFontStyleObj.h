#ifndef CLASSES_LAYER_LAYERFONTSTYLEOBJ_H
#define CLASSES_LAYER_LAYERFONTSTYLEOBJ_H

#include "layer/LayerStrInfo.h"
#include "layer/LayerBase.h"
#include "layer/LayerAccFontStyle.h"

namespace layer { class LayerFontManager; }

namespace layer {
// table 0x7100B806A0
// A LayerBase: its table has LayerBase's shape (slot 0 destructor, slot 2 release), and the layer accessors hand
// their LayerBase* to its methods unadjusted (LayerAccFontObj::setMsg/setColorMap, LayerAccFontStyle).
class LayerFontStyleObj : public ::layer::LayerBase {
public:
    // 1.0.0's constructor (out of line there, inline in LayerFontManager::createStyleObj in 3.0.1)
    LayerFontStyleObj(LayerFontManager* manager)
        : m_state(0xCC), m_strings(nullptr), m_styleDataMax(0), m_styleData(nullptr), m_manager(manager),
          m_ratio(0.4f), m_colorInfo(nullptr), m_iconInfo(nullptr) {
        m_prev = nullptr;
        m_next = nullptr;
        m_objType = 9;
    }
    virtual ~LayerFontStyleObj();  // slot 0
    virtual void release();  // slot 2
    // the style-th record (the first past the last)
    const LyrFontStyleData* getStyleData(unsigned int style) const;
    const char* getFontName(unsigned int style) const;
    mm::mtl::Vector<LayerStrInfo>* createColorInfo(unsigned int count);
    mm::mtl::Vector<LayerStrInfo>* createIconInfo(unsigned int count);
    // 1.0.0's (inline in 3.0.1): data is the style resource
    void setStyleData(const void* data) {
        const unsigned char* res = static_cast<const unsigned char*>(data);
        m_strings = static_cast<const char*>(data);
        m_styleDataMax = *reinterpret_cast<const unsigned int*>(res + 0xC);
        m_styleData = reinterpret_cast<const LyrFontStyleData*>(res + *reinterpret_cast<const unsigned int*>(res + 0x8));
    }
    // 1.0.0's (inline in 3.0.1)
    void releaseColorInfo() {
        if (m_colorInfo != nullptr) {
            delete m_colorInfo;
            m_colorInfo = nullptr;
        }
    }
    void releaseIconInfo() {
        if (m_iconInfo != nullptr) {
            delete m_iconInfo;
            m_iconInfo = nullptr;
        }
    }

    // The field names follow LayerAccFontStyle's accessors that read them (not the original's).
    unsigned char m_state;  // 0x1C: 0xCC when made, 0x22 once released
    unsigned char pad_1D[0x3];
    const char* m_strings;  // getStyleInfo
    unsigned int m_styleDataMax;  // getStyleDataMax
    unsigned char pad_2C[0x4];
    const LyrFontStyleData* m_styleData;  // getStyleInfo
    LayerFontManager* m_manager;  // 0x38: whose m_styleList holds it
    float m_ratio;  // 0x40: 0.4 from the constructor (the name is not the original's; its use is not known yet)
    unsigned char pad_44[0x4];
    mm::mtl::Vector<LayerStrInfo>* m_colorInfo;  // 0x48: createColorInfo's
    mm::mtl::Vector<LayerStrInfo>* m_iconInfo;   // 0x50: createIconInfo's
};
}  // namespace layer

#endif
