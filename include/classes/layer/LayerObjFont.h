#ifndef CLASSES_LAYER_LAYEROBJFONT_H
#define CLASSES_LAYER_LAYEROBJFONT_H
#include "classes/layer/LayerObj.h"
#include "layer/LayerAccFontObj.h"

namespace layer { class LayerFontIconObj; }
namespace layer { class LayerFontResObj; }
namespace layer { class LayerFontStyleObj; }

namespace layer {
// a font layer object. Derived from LayerObj: LayerAccFontObj hands its layer object to these methods unadjusted, and
// its fields follow LayerObj's. The field names follow LayerAccFontObj's accessors (not the original's).
class LayerObjFont : public ::layer::LayerObj {
public:
    void setMsg(const unsigned char* text, const LayerFontResObj* font, const LayerFontStyleObj* style,
                const LayerFontIconObj* icon, unsigned int styleIndex);
    void setColorMap(const LayerFontIconObj* colorMap, unsigned int pattern);
    void setBorderWeight(float weight);
    void setSlopeRot(float rot);
    float getBorderWeight() const;
    float getSlopeRot() const;

    unsigned char pad_248[0x30];
    // what setMsg(text) draws with (named after setMsg's parameters)
    const LayerFontResObj* m_font;
    const LayerFontStyleObj* m_style;
    const LayerFontIconObj* m_icon;
    const LayerFontIconObj* m_colorMap;  // setColorMap
    unsigned int m_styleIndex;  // setMsg(text)
    unsigned int m_colorMapPattern;  // setColorMap
    unsigned short m_fontPixelX;  // getFontPixelX
    unsigned short m_fontPixelY;  // getFontPixelY
    unsigned short m_fontPixelWidth;  // getFontPixelWidth
    unsigned short m_fontPixelHeight;  // getFontPixelHeight
    LayerFontHorizontal m_horizontal;  // set/getHorizontal
    LayerFontVertical m_vertical;  // set/getVertical
    LayerFontDisplayArea m_displayArea;  // set/getDisplayArea
    LayerFontSetting m_dispSetting;  // setDispSetting
    float m_slopeRot;  // setSlopeRot
};
}  // namespace layer

#endif
