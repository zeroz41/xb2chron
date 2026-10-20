#ifndef CLASSES_ML_CACHEDRAW_DFONT64_H
#define CLASSES_ML_CACHEDRAW_DFONT64_H

#include "classes/ml/CacheDraw.h"

namespace ml { class DebDraw; }

namespace ml {
// table 0x7100B77198
class CacheDraw::DFONT64 {
public:
    virtual void flush(ml::DebDraw*);  // slot 0
};
}  // namespace ml

#endif
