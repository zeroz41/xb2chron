#ifndef CLASSES_ML_CACHEDRAW_DALPHA_BLEND_H
#define CLASSES_ML_CACHEDRAW_DALPHA_BLEND_H

#include "classes/ml/CacheDraw.h"

namespace ml { class DebDraw; }

namespace ml {
// table 0x7100B770F0
class CacheDraw::DALPHA_BLEND : public CacheDraw::CMD {
public:
    DALPHA_BLEND(bool blend) : CMD(0x31, 0, sizeof(DALPHA_BLEND)), m_blend(blend) {}
    virtual void flush(ml::DebDraw*);  // slot 0

    bool m_blend;  // 0x0C (the name is not the original's)
};
}  // namespace ml

#endif
