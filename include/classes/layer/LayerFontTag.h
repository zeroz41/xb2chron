#ifndef CLASSES_LAYER_LAYERFONTTAG_H
#define CLASSES_LAYER_LAYERFONTTAG_H

namespace layer {
// table none (its derived classes')
class LayerFontTag {
public:
    virtual ~LayerFontTag();  // slot 0
    virtual void beginParseString();  // slot 2
    virtual void endParseString();  // slot 3
    virtual void parseNotTag(unsigned char const*, unsigned int&);  // slot 4
    virtual void parseNotTag(wchar_t const*, unsigned int&);  // slot 5
    virtual void vf6();  // slot 6
    virtual void callTagEnd(char const*);  // slot 7
};
}  // namespace layer

#endif
