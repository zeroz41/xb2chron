#ifndef CLASSES_ML_CACHEDRAW_DRRECT_H
#define CLASSES_ML_CACHEDRAW_DRRECT_H

#include "classes/ml/CacheDraw.h"
#include "mm/Rect.h"

namespace ml { class DebDraw; }

namespace ml {
// table 0x7100B76F70
class CacheDraw::DRRECT : public CacheDraw::CMD {
public:
    DRRECT(const mm::Rect<int>& rect) : CMD(0xA, 1, sizeof(DRRECT)), m_rect(rect) {}
    virtual void flush(ml::DebDraw*);  // slot 0

    mm::Rect<int> m_rect;  // 0x0C (the name is not the original's)
};
}  // namespace ml

#endif
