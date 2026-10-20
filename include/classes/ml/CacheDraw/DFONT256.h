#ifndef CLASSES_ML_CACHEDRAW_DFONT256_H
#define CLASSES_ML_CACHEDRAW_DFONT256_H

#include "classes/ml/CacheDraw.h"

namespace ml { class DebDraw; }

namespace ml {
// table 0x7100B771C8
class CacheDraw::DFONT256 {
public:
    virtual void flush(ml::DebDraw*);  // slot 0
};
}  // namespace ml

#endif
