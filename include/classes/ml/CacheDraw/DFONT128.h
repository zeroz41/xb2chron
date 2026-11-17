#ifndef CLASSES_ML_CACHEDRAW_DFONT128_H
#define CLASSES_ML_CACHEDRAW_DFONT128_H

#include "classes/ml/CacheDraw.h"
#include "mm/Pnt.h"
#include "mm/mtl/FixStr.h"

namespace ml { class DebDraw; }

namespace ml {
// table 0x7100B771B0
class CacheDraw::DFONT128 : public CacheDraw::CMD {
public:
    // CacheDraw::font queues it for a text shorter than 128 characters
    DFONT128(short x, short y, const char* text) : CMD(0x3a, 0, sizeof(DFONT128)), m_pos(x, y) {
        m_text = text;
    }
    virtual void flush(ml::DebDraw*);  // slot 0

    mm::mtl::FixStr<0x80> m_text;  // 0x0C (the name is not the original's)
    mm::Pnt<short> m_pos;  // 0x90 (the name is not the original's)
};
}  // namespace ml

#endif
