#ifndef CLASSES_ML_CACHEDRAW_DFONT_COL_H
#define CLASSES_ML_CACHEDRAW_DFONT_COL_H

#include "classes/ml/CacheDraw.h"
#include "mm/Col4.h"

namespace ml { class DebDraw; }

namespace ml {
// table 0x7100B771E0
class CacheDraw::DFONT_COL : public CacheDraw::CMD {
public:
    virtual void flush(ml::DebDraw*);  // slot 0

    mm::Col4 m_col;  // 0x0C (the name is not the original's)
};
}  // namespace ml

#endif
