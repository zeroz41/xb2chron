#ifndef CLASSES_ML_CACHEDRAW_DRCIRCLE_MAT_H
#define CLASSES_ML_CACHEDRAW_DRCIRCLE_MAT_H

#include "classes/ml/CacheDraw.h"
#include "mm/Mat44.h"

namespace ml { class DebDraw; }

namespace ml {
// table 0x7100B76FB8
class CacheDraw::DRCIRCLE_MAT : public CacheDraw::CMD {
public:
    DRCIRCLE_MAT(const mm::Mat44& mtx, float radius, unsigned int div)
        : CMD(0x15, 2, sizeof(DRCIRCLE_MAT)) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                m_mtx[i][j] = mtx.m[i][j];
            }
        }
        m_radius = radius;
        m_div = div;
    }
    virtual void flush(ml::DebDraw*);  // slot 0
    // the command keeps the matrix unaligned at 0x0C and hands DebDraw a mm::Mat44 view of it
    const mm::Mat44& mat() const { return reinterpret_cast<const mm::Mat44&>(m_mtx); }

    float m_mtx[4][4];  // 0x0C (the name is not the original's)
    float m_radius;  // 0x4C (the name is not the original's)
    unsigned int m_div;  // 0x50 (the name is not the original's)
};
}  // namespace ml

#endif
