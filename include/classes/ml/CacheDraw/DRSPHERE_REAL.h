#ifndef CLASSES_ML_CACHEDRAW_DRSPHERE_REAL_H
#define CLASSES_ML_CACHEDRAW_DRSPHERE_REAL_H

#include "classes/ml/CacheDraw.h"

namespace ml { class DebDraw; }

namespace ml {
// table 0x7100B77018
class CacheDraw::DRSPHERE_REAL : public CacheDraw::CMD {
public:
    DRSPHERE_REAL(float radius, unsigned int div) : CMD(0x1E, 2, sizeof(DRSPHERE_REAL)), m_radius(radius), m_div(div) {}
    virtual void flush(ml::DebDraw*);  // slot 0

    float m_radius;  // 0x0C (the name is not the original's)
    unsigned int m_div;  // 0x10 (the name is not the original's)
};
}  // namespace ml

#endif
