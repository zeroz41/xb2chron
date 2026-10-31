#ifndef CLASSES_ML_CACHEDRAW_DZWRITE_H
#define CLASSES_ML_CACHEDRAW_DZWRITE_H

#include "classes/ml/CacheDraw.h"

namespace ml { class DebDraw; }

namespace ml {
// table 0x7100B76F58
class CacheDraw::DZWRITE : public CacheDraw::CMD {
public:
    DZWRITE(bool on) : CMD(0x8, 0, sizeof(DZWRITE)), m_on(on) {}
    virtual void flush(ml::DebDraw*);  // slot 0

    bool m_on;  // 0x0C (the name is not the original's)
};
}  // namespace ml

#endif
