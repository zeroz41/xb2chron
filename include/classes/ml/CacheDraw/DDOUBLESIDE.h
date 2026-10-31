#ifndef CLASSES_ML_CACHEDRAW_DDOUBLESIDE_H
#define CLASSES_ML_CACHEDRAW_DDOUBLESIDE_H

#include "classes/ml/CacheDraw.h"

namespace ml { class DebDraw; }

namespace ml {
// table 0x7100B76F28
class CacheDraw::DDOUBLESIDE : public CacheDraw::CMD {
public:
    DDOUBLESIDE(const bool& doubleSide) : CMD(6, 0, sizeof(DDOUBLESIDE)), m_doubleSide(doubleSide) {}
    virtual void flush(ml::DebDraw*);  // slot 0
    bool m_doubleSide;  // 0x0C (the name is not the original's)
};
}  // namespace ml

#endif
