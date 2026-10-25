#ifndef CLASSES_ML_CACHEDRAW_DFONT128_H
#define CLASSES_ML_CACHEDRAW_DFONT128_H

#include "classes/ml/CacheDraw.h"
#include "mm/Pnt.h"

namespace ml { class DebDraw; }

namespace ml {
// table 0x7100B771B0
class CacheDraw::DFONT128 : public CacheDraw::CMD {
public:
    virtual void flush(ml::DebDraw*);  // slot 0

    char m_text[0x80];  // 0x0C (the name is not the original's)
    unsigned char pad_8c[0x4];
    mm::Pnt<short> m_pos;  // 0x90 (the name is not the original's)
};
}  // namespace ml

#endif
