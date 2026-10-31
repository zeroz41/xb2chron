#ifndef CLASSES_EVENT_TEXTCAPTION_H
#define CLASSES_EVENT_TEXTCAPTION_H

#include "mm/mtl/FixStr.h"

namespace event {
// table 0x7100B3D630
class TextCaption {
public:
    // built in place by TextManager's constructor (inlined into every Singleton<TextManager>::getPtr); size 0x110
    TextCaption() : pad_8(0) {}
    virtual ~TextCaption() {}  // slot 0
    unsigned int pad_8;
    mm::mtl::FixStr<256> pad_c;  // a 256-byte string (emptied by the constructor)
};
}  // namespace event

#endif
