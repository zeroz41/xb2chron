#ifndef CLASSES_ML_CACHEDRAW_DRAXIS_H
#define CLASSES_ML_CACHEDRAW_DRAXIS_H

#include "classes/ml/CacheDraw.h"

namespace ml { class DebDraw; }

namespace ml {
// table 0x7100B76FD0
class CacheDraw::DRAXIS : public CacheDraw::CMD {
public:
    DRAXIS(float length) : CMD(0x18, 2, sizeof(DRAXIS)), m_length(length) {}
    virtual void flush(ml::DebDraw*);  // slot 0

    float m_length;  // 0x0C (the name is not the original's)
};
}  // namespace ml

#endif
