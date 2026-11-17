#ifndef CLASSES_ML_CACHEDRAW_DFONT32_H
#define CLASSES_ML_CACHEDRAW_DFONT32_H

#include "classes/ml/CacheDraw.h"
#include "mm/Pnt.h"
#include "mm/mtl/FixStr.h"

namespace ml { class DebDraw; }

namespace ml {
// table 0x7100B77180
class CacheDraw::DFONT32 : public CacheDraw::CMD {
public:
    // CacheDraw::font queues it for a text shorter than 32 characters
    DFONT32(short x, short y, const char* text) : CMD(0x38, 0, sizeof(DFONT32)), m_pos(x, y) {
        m_text = text;
    }
    virtual void flush(ml::DebDraw*);  // slot 0

    mm::mtl::FixStr<0x20> m_text;  // 0x0C (the name is not the original's)
    mm::Pnt<short> m_pos;  // 0x30 (the name is not the original's)
};
}  // namespace ml

#endif
