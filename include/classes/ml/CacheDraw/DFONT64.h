#ifndef CLASSES_ML_CACHEDRAW_DFONT64_H
#define CLASSES_ML_CACHEDRAW_DFONT64_H

#include "classes/ml/CacheDraw.h"
#include "mm/Pnt.h"

namespace ml { class DebDraw; }

namespace ml {
// table 0x7100B77198
class CacheDraw::DFONT64 : public CacheDraw::CMD {
public:
    virtual void flush(ml::DebDraw*);  // slot 0

    char m_text[0x40];  // 0x0C (the name is not the original's)
    unsigned char pad_4c[0x4];
    mm::Pnt<short> m_pos;  // 0x50 (the name is not the original's)
};
}  // namespace ml

#endif
