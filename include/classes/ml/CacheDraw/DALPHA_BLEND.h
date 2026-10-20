#ifndef CLASSES_ML_CACHEDRAW_DALPHA_BLEND_H
#define CLASSES_ML_CACHEDRAW_DALPHA_BLEND_H

#include "classes/ml/CacheDraw.h"

namespace ml { class DebDraw; }

namespace ml {
// table 0x7100B770F0
class CacheDraw::DALPHA_BLEND {
public:
    virtual void flush(ml::DebDraw*);  // slot 0
};
}  // namespace ml

#endif
