#ifndef CLASSES_ML_CACHEDRAW_DRLINE_PNT_H
#define CLASSES_ML_CACHEDRAW_DRLINE_PNT_H

#include "classes/ml/CacheDraw.h"
#include "mm/Pnt.h"

namespace ml { class DebDraw; }

namespace ml {
// table 0x7100B770C0
class CacheDraw::DRLINE_PNT : public CacheDraw::CMD {
public:
    DRLINE_PNT(const mm::Pnt<int>& start, const mm::Pnt<int>& end) : CMD(0x2D, 1, sizeof(DRLINE_PNT)), m_start(start), m_end(end) {}
    virtual void flush(ml::DebDraw*);  // slot 0

    mm::Pnt<int> m_start;  // 0x0C (the name is not the original's)
    mm::Pnt<int> m_end;  // 0x14 (the name is not the original's)
};
}  // namespace ml

#endif
