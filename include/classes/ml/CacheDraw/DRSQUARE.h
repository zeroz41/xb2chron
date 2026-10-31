#ifndef CLASSES_ML_CACHEDRAW_DRSQUARE_H
#define CLASSES_ML_CACHEDRAW_DRSQUARE_H

#include "classes/ml/CacheDraw.h"

namespace ml { class DebDraw; }

namespace ml {
// table 0x7100B77090
class CacheDraw::DRSQUARE : public CacheDraw::CMD {
public:
    DRSQUARE(float width, float height) : CMD(0x27, 2, sizeof(DRSQUARE)), m_width(width), m_height(height) {}
    virtual void flush(ml::DebDraw*);  // slot 0

    float m_width;  // 0x0C (the name is not the original's)
    float m_height;  // 0x10 (the name is not the original's)
};
}  // namespace ml

#endif
