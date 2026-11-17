#ifndef CLASSES_ML_CACHEDRAW_DFONT64_H
#define CLASSES_ML_CACHEDRAW_DFONT64_H

#include "classes/ml/CacheDraw.h"
#include "mm/Pnt.h"
#include "mm/mtl/FixStr.h"

namespace ml { class DebDraw; }

namespace ml {
// table 0x7100B77198
class CacheDraw::DFONT64 : public CacheDraw::CMD {
public:
    // CacheDraw::font queues it for a text shorter than 64 characters
    DFONT64(short x, short y, const char* text) : CMD(0x39, 0, sizeof(DFONT64)), m_pos(x, y) {
        m_text = text;
    }
    virtual void flush(ml::DebDraw*);  // slot 0

    mm::mtl::FixStr<0x40> m_text;  // 0x0C (the name is not the original's)
    mm::Pnt<short> m_pos;  // 0x50 (the name is not the original's)
};
}  // namespace ml

#endif
