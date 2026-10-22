#ifndef LAYER_LAYERACCFONTOBJ_H
#define LAYER_LAYERACCFONTOBJ_H

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

// access to a font layer object
class LayerAccFontObj {
public:
    LayerAccFontObj(LayerBase* layer);
    void setDispSetting(LayerFontSetting setting);
    void setHorizontal(LayerFontHorizontal horizontal);
    void setVertical(LayerFontVertical vertical);
    void setDisplayArea(LayerFontDisplayArea area);
    void setBorderWeight(float weight);
    void setSlopeRot(float rot);
    LayerFontHorizontal getHorizontal() const;
    LayerFontVertical getVertical() const;
    float getBorderWeight() const;
    float getSlopeRot() const;
    short getFontPixelX() const;  // the text's offset in its object
    short getFontPixelY() const;
    void setMsg(const char* text, const LayerBase* font, unsigned int style);  // in that font and style
    void setMsg(const char* text);
    void setColorMap(const LayerBase* colorMap, unsigned int pattern);

    LayerBase* m_layer;  // the constructor's
};
}  // namespace layer

#endif
