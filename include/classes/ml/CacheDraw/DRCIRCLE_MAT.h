#ifndef CLASSES_ML_CACHEDRAW_DRCIRCLE_MAT_H
#define CLASSES_ML_CACHEDRAW_DRCIRCLE_MAT_H

#include "classes/ml/CacheDraw.h"

namespace ml { class DebDraw; }

namespace ml {
// table 0x7100B76FB8
class CacheDraw::DRCIRCLE_MAT {
public:
    virtual void flush(ml::DebDraw*);  // slot 0
};
}  // namespace ml

#endif
