#ifndef CLASSES_ML_CACHEDRAW_DZCOMP_H
#define CLASSES_ML_CACHEDRAW_DZCOMP_H

#include "classes/ml/CacheDraw.h"

namespace ml { class DebDraw; }

namespace ml {
// table 0x7100B76F40
class CacheDraw::DZCOMP : public CacheDraw::CMD {
public:
    DZCOMP(const bool& on) : CMD(0x7, 0, sizeof(DZCOMP)), m_on(on) {}
    virtual void flush(ml::DebDraw*);  // slot 0

    bool m_on;  // 0x0C (the name is not the original's)
};
}  // namespace ml

#endif
