#ifndef CLASSES_ML_CACHEDRAW_DRRECT_FILL_H
#define CLASSES_ML_CACHEDRAW_DRRECT_FILL_H

#include "classes/ml/CacheDraw.h"
#include "mm/Rect.h"

namespace ml { class DebDraw; }

namespace ml {
// table 0x7100B76F88
class CacheDraw::DRRECT_FILL : public CacheDraw::CMD {
public:
    DRRECT_FILL(const mm::Rect<int>& rect) : CMD(0xB, 1, sizeof(DRRECT_FILL)), m_rect(rect) {}
    virtual void flush(ml::DebDraw*);  // slot 0

    mm::Rect<int> m_rect;  // 0x0C (the name is not the original's)
};
}  // namespace ml

#endif
