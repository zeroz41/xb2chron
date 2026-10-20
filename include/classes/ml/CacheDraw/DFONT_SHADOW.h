#ifndef CLASSES_ML_CACHEDRAW_DFONT_SHADOW_H
#define CLASSES_ML_CACHEDRAW_DFONT_SHADOW_H

#include "classes/ml/CacheDraw.h"

namespace ml { class DebDraw; }

namespace ml {
// table 0x7100B771F8
class CacheDraw::DFONT_SHADOW {
public:
    virtual void flush(ml::DebDraw*);  // slot 0
};
}  // namespace ml

#endif
