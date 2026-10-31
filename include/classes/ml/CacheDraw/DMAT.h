#ifndef CLASSES_ML_CACHEDRAW_DMAT_H
#define CLASSES_ML_CACHEDRAW_DMAT_H

#include "classes/ml/CacheDraw.h"
#include "mm/Mat44.h"

namespace ml { class DebDraw; }

namespace ml {
// table 0x7100B76EB0
class CacheDraw::DMAT : public CacheDraw::CMD {
public:
    DMAT(const mm::Mat44& mtx) : CMD(0x2, 2, sizeof(DMAT)), m_mtx(mtx) {}
    virtual void flush(ml::DebDraw*);  // slot 0

    mm::Mat44 m_mtx;  // 0x10 (the name is not the original's)
};
}  // namespace ml

#endif
