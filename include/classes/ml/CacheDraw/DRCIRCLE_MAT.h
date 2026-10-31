#ifndef CLASSES_ML_CACHEDRAW_DRCIRCLE_MAT_H
#define CLASSES_ML_CACHEDRAW_DRCIRCLE_MAT_H

#include "classes/ml/CacheDraw.h"
#include "mm/Mat44.h"

namespace ml { class DebDraw; }

namespace ml {
// table 0x7100B76FB8
class CacheDraw::DRCIRCLE_MAT : public CacheDraw::CMD {
public:
    // command 0x15, kind 2, 0x58 bytes (CacheDraw's queueing function is not written yet)
    virtual void flush(ml::DebDraw*);  // slot 0
    // the command keeps the matrix unaligned at 0x0C and hands DebDraw a mm::Mat44 view of it
    const mm::Mat44& mat() const { return reinterpret_cast<const mm::Mat44&>(m_mtx); }

    float m_mtx[4][4];  // 0x0C (the name is not the original's)
    float m_radius;  // 0x4C (the name is not the original's)
    unsigned int m_div;  // 0x50 (the name is not the original's)
};
}  // namespace ml

#endif
