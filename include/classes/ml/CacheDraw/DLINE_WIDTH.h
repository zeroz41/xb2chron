#ifndef CLASSES_ML_CACHEDRAW_DLINE_WIDTH_H
#define CLASSES_ML_CACHEDRAW_DLINE_WIDTH_H

#include "classes/ml/CacheDraw.h"

namespace ml { class DebDraw; }

namespace ml {
// table 0x7100B770D8
class CacheDraw::DLINE_WIDTH {
public:
    virtual void flush(ml::DebDraw*);  // slot 0
};
}  // namespace ml

#endif
