#ifndef CLASSES_ML_CACHEDRAW_DRLINE_H
#define CLASSES_ML_CACHEDRAW_DRLINE_H

#include "classes/ml/CacheDraw.h"

namespace ml { class DebDraw; }

namespace ml {
// table 0x7100B770A8
class CacheDraw::DRLINE {
public:
    virtual void flush(ml::DebDraw*);  // slot 0
};
}  // namespace ml

#endif
