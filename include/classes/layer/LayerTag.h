#ifndef CLASSES_LAYER_LAYERTAG_H
#define CLASSES_LAYER_LAYERTAG_H

namespace layer { class LayerTagTbl; }

namespace layer {
// table none (its derived classes')
class LayerTag {
public:
    virtual ~LayerTag() {}  // slot 0
    virtual void beginParseString() = 0;  // slot 2
    virtual void endParseString() = 0;  // slot 3
    virtual void parseNotTag(unsigned char const*, unsigned int&) = 0;  // slot 4
    virtual void parseNotTag(wchar_t const*, unsigned int&) = 0;  // slot 5
    virtual void callTagStart(char const*, layer::LayerTagTbl const*, unsigned int);  // slot 6
    virtual void callTagEnd(char const*);  // slot 7
};
}  // namespace layer

#endif
