#ifndef CLASSES_ML_CACHEDRAW_DFONT_SCALE_H
#define CLASSES_ML_CACHEDRAW_DFONT_SCALE_H

#include "classes/ml/CacheDraw.h"

namespace ml { class DebDraw; }

namespace ml {
// table 0x7100B77228
class CacheDraw::DFONT_SCALE {
public:
    virtual void flush(ml::DebDraw*);  // slot 0
};
}  // namespace ml

#endif
