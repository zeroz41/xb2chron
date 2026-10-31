#ifndef CLASSES_ML_CACHEDRAW_DCOL_H
#define CLASSES_ML_CACHEDRAW_DCOL_H

#include "classes/ml/CacheDraw.h"
#include "mm/Col4.h"

namespace ml { class DebDraw; }

namespace ml {
// table 0x7100B76F10
class CacheDraw::DCOL : public CacheDraw::CMD {
public:
    DCOL(const mm::Col4& col) : CMD(0x5, 0, sizeof(DCOL)), m_col(col) {}
    virtual void flush(ml::DebDraw*);  // slot 0

    mm::Col4 m_col;  // 0x0C (the name is not the original's)
};
}  // namespace ml

#endif
