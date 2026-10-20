#ifndef CLASSES_ML_CACHEDRAW_DRLINE_PNT_H
#define CLASSES_ML_CACHEDRAW_DRLINE_PNT_H

#include "classes/ml/CacheDraw.h"

namespace ml { class DebDraw; }

namespace ml {
// table 0x7100B770C0
class CacheDraw::DRLINE_PNT {
public:
    virtual void flush(ml::DebDraw*);  // slot 0
};
}  // namespace ml

#endif
