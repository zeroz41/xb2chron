#ifndef CLASSES_LAYER_LAYERTAG_H
#define CLASSES_LAYER_LAYERTAG_H

namespace layer {
// a tag's parameters as LayerTag::callTagStart hands them on: name and value side by side (ui::UITagParser::
// callTagStart looks a parameter's value up by its name; the names are not the original's)
class LayerTagTbl {
public:
    const char* m_name;
    const char* m_value;
};
}  // namespace layer

namespace layer {
// table none (its derived classes')
class LayerTag {
public:
    virtual ~LayerTag() {}  // slot 0
    virtual void beginParseString() = 0;  // slot 2
    virtual void endParseString() {}  // slot 3 (LayerFontDrawBuffer's table holds LayerTag's)
    virtual void parseNotTag(unsigned char const*, unsigned int&) = 0;  // slot 4
    virtual void parseNotTag(wchar_t const*, unsigned int&) = 0;  // slot 5
    // whether the tag was taken (LayerTag::callTagEnd returns false)
    virtual bool callTagStart(char const*, layer::LayerTagTbl const*, unsigned int) { return false; }  // slot 6
    virtual bool callTagEnd(char const*) { return false; }  // slot 7
    virtual void callTagNoUse(unsigned char const*) {}  // slot 8 (LayerFontDrawBuffer's table holds LayerTag's)
    void calcParseString(const unsigned char* text);      // reads text's tags, calling callTagStart and callTagEnd
    void calcUTF8ParseString(const unsigned char* text);  // the same for UTF-8 text
};
}  // namespace layer

#endif
