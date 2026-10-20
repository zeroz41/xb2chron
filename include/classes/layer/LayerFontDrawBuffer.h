// not proven yet: its table differs from the original's (word 5: _ZN5layer12LayerFontTag14endParseStringEv where the original has _ZN5layer8LayerTag14endParseStringEv)
#ifndef CLASSES_LAYER_LAYERFONTDRAWBUFFER_H
#define CLASSES_LAYER_LAYERFONTDRAWBUFFER_H

#include "classes/layer/LayerFontTag.h"

namespace layer {
// table 0x7100B805C8
class LayerFontDrawBuffer : public ::layer::LayerFontTag {
public:
    virtual ~LayerFontDrawBuffer();  // slot 0
    virtual void callTagNoUse(unsigned char const*);  // slot 8
    virtual void createFontCode(unsigned short);  // slot 9
    virtual void createRubyFontCode(unsigned short);  // slot 10
    virtual void createFontIcon(unsigned short);  // slot 11
    virtual void createLineBreak();  // slot 12
};
}  // namespace layer

#endif
