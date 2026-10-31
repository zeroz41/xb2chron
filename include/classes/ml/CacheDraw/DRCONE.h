#ifndef CLASSES_ML_CACHEDRAW_DRCONE_H
#define CLASSES_ML_CACHEDRAW_DRCONE_H

#include "classes/ml/CacheDraw.h"

namespace ml { class DebDraw; }

namespace ml {
// table 0x7100B77048
class CacheDraw::DRCONE : public CacheDraw::CMD {
public:
    DRCONE(float radius, float height, unsigned int div) : CMD(0x20, 2, sizeof(DRCONE)), m_radius(radius), m_height(height), m_div(div) {}
    virtual void flush(ml::DebDraw*);  // slot 0

    float m_radius;  // 0x0C (the name is not the original's)
    float m_height;  // 0x10 (the name is not the original's)
    unsigned int m_div;  // 0x14 (the name is not the original's)
};
}  // namespace ml

#endif
