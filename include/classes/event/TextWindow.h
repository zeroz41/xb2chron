#ifndef CLASSES_EVENT_TEXTWINDOW_H
#define CLASSES_EVENT_TEXTWINDOW_H

#include "mm/mtl/FixStr.h"

namespace event {
// table 0x7100B3D610
class TextWindow {
public:
    // built in place by TextManager's constructor (inlined into every Singleton<TextManager>::getPtr); size 0x298
    TextWindow() : pad_8(0), pad_218(-1), pad_220(0), pad_250(0), pad_25c(0) {}
    virtual ~TextWindow() {}  // slot 0
    unsigned int pad_8;
    mm::mtl::FixStr<256> pad_c;    // two 256-byte strings (emptied by the constructor)
    mm::mtl::FixStr<256> pad_110;
    unsigned int pad_214;
    long pad_218;  // -1 after construction
    unsigned long pad_220;
    unsigned char pad_228[0x8];
    // 0x230..0x25d: zeroed by TextManager::init (one memset of 0x2d bytes)
    unsigned char pad_230[0x20];
    unsigned long pad_250;
    unsigned char pad_258[0x4];
    unsigned char pad_25c;
    unsigned char pad_25d[0x3b];
};
}  // namespace event

#endif
