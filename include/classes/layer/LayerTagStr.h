#ifndef CLASSES_LAYER_LAYERTAGSTR_H
#define CLASSES_LAYER_LAYERTAGSTR_H

#include "classes/layer/LayerTag.h"

namespace layer {
// table 0x7100B7F910
class LayerTagStr : public ::layer::LayerTag {
public:
    virtual ~LayerTagStr();  // slot 0
    virtual void beginParseString();  // slot 2
    virtual void endParseString();  // slot 3
    virtual void parseNotTag(unsigned char const*, unsigned int&);  // slot 4
    virtual void parseNotTag(wchar_t const*, unsigned int&);  // slot 5
    virtual void callTagNoUse(unsigned char const*);  // slot 8
    unsigned char pad_8[0x10];  // fields: size from its derived classes
};
}  // namespace layer

#endif
