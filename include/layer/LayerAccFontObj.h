#ifndef LAYER_LAYERACCFONTOBJ_H
#define LAYER_LAYERACCFONTOBJ_H

#include "layer/LayerAccObjBase.h"

namespace layer { class LayerBase; }

namespace layer {
// how a font object lays out its text (setDispSetting stores it in the layer object)
enum LayerFontSetting {};
// whether a font object's text fills its area (UITextObject::create sets 1, setTextAlignH 0 for aligned text)
enum LayerFontDisplayArea {};
// a font object's horizontal alignment (0-2: UITextObject::setTextAlignH's)
enum LayerFontHorizontal {};
// a font object's vertical alignment (0-2: UITextObject::setTextAlignV's)
enum LayerFontVertical {};

// access to a font layer object; a LayerAccObjBase (UIObject::applyTransform reads a font object's pixel size
// through LayerAccObjBase::getPixelWidth/getPixelHeight on it)
class LayerAccFontObj : public LayerAccObjBase {
public:
    LayerAccFontObj(LayerBase* layer);
    unsigned short getFontPixelWidth() const;
    unsigned short getFontPixelHeight() const;
    void setDispSetting(LayerFontSetting setting);
    void setHorizontal(LayerFontHorizontal horizontal);
    void setVertical(LayerFontVertical vertical);
    void setDisplayArea(LayerFontDisplayArea area);
    void setBorderWeight(float weight);
    void setSlopeRot(float rot);
    LayerFontHorizontal getHorizontal() const;
    LayerFontVertical getVertical() const;
    LayerFontDisplayArea getDisplayArea() const;
    float getBorderWeight() const;
    float getSlopeRot() const;
    short getFontPixelX() const;  // the text's offset in its object
    short getFontPixelY() const;
    void setMsg(const char* text, const LayerBase* font, unsigned int style);  // in that font and style
    void setMsg(const char* text);
    void setColorMap(const LayerBase* colorMap, unsigned int pattern);
};
}  // namespace layer

#endif
