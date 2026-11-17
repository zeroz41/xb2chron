#ifndef CLASSES_ML_CACHEDRAW_DFONT256_H
#define CLASSES_ML_CACHEDRAW_DFONT256_H

#include "classes/ml/CacheDraw.h"
#include "mm/Pnt.h"
#include "mm/mtl/FixStr.h"

namespace ml { class DebDraw; }

namespace ml {
// table 0x7100B771C8
class CacheDraw::DFONT256 : public CacheDraw::CMD {
public:
    // CacheDraw::font queues it for a text shorter than 256 characters
    DFONT256(short x, short y, const char* text) : CMD(0x3b, 0, sizeof(DFONT256)), m_pos(x, y) {
        m_text = text;
    }
    virtual void flush(ml::DebDraw*);  // slot 0

    mm::mtl::FixStr<0x100> m_text;  // 0x0C (the name is not the original's)
    mm::Pnt<short> m_pos;  // 0x110 (the name is not the original's)
};
}  // namespace ml

#endif
