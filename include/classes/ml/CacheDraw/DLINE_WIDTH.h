#ifndef CLASSES_ML_CACHEDRAW_DLINE_WIDTH_H
#define CLASSES_ML_CACHEDRAW_DLINE_WIDTH_H

#include "classes/ml/CacheDraw.h"

namespace ml { class DebDraw; }

namespace ml {
// table 0x7100B770D8
class CacheDraw::DLINE_WIDTH : public CacheDraw::CMD {
public:
    DLINE_WIDTH(unsigned int width) : CMD(0x30, 0, sizeof(DLINE_WIDTH)), m_width(width) {}
    virtual void flush(ml::DebDraw*);  // slot 0
    unsigned int m_width;  // 0x0C (the name is not the original's)
};
}  // namespace ml

#endif
