#ifndef CLASSES_EVENT_TEXTCAPTION_H
#define CLASSES_EVENT_TEXTCAPTION_H

#include "mm/mtl/FixStr.h"

namespace event {
// table 0x7100B3D630
class TextCaption {
public:
    // built in place by TextManager's constructor (inlined into every Singleton<TextManager>::getPtr); size 0x110
    TextCaption() : m_flags(0) {}
    virtual ~TextCaption() {}  // slot 0
    void render();
    // bit 0: a caption is shown (TextManager::write sets it, render draws only then); the name is not the original's
    unsigned int m_flags;
    mm::mtl::FixStr<256> m_text;  // the caption render draws under "CAPTION" (the name is not the original's)
};
}  // namespace event

#endif
