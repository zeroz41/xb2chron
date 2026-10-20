#ifndef CLASSES_ML_CACHEDRAW_DFONT32_H
#define CLASSES_ML_CACHEDRAW_DFONT32_H

#include "classes/ml/CacheDraw.h"

namespace ml { class DebDraw; }

namespace ml {
// table 0x7100B77180
class CacheDraw::DFONT32 {
public:
    virtual void flush(ml::DebDraw*);  // slot 0
};
}  // namespace ml

#endif
