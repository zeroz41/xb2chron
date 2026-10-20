#ifndef CLASSES_ML_CACHEDRAW_DFONT128_H
#define CLASSES_ML_CACHEDRAW_DFONT128_H

#include "classes/ml/CacheDraw.h"

namespace ml { class DebDraw; }

namespace ml {
// table 0x7100B771B0
class CacheDraw::DFONT128 {
public:
    virtual void flush(ml::DebDraw*);  // slot 0
};
}  // namespace ml

#endif
