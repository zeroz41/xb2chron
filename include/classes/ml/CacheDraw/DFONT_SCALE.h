#ifndef CLASSES_ML_CACHEDRAW_DFONT_SCALE_H
#define CLASSES_ML_CACHEDRAW_DFONT_SCALE_H

#include "classes/ml/CacheDraw.h"

namespace ml { class DebDraw; }

namespace ml {
// table 0x7100B77228
class CacheDraw::DFONT_SCALE : public CacheDraw::CMD {
public:
    virtual void flush(ml::DebDraw*);  // slot 0

    float m_x;  // 0x0C (the name is not the original's)
    float m_y;  // 0x10 (the name is not the original's)
};
}  // namespace ml

#endif
