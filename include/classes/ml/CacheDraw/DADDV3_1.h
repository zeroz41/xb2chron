#ifndef CLASSES_ML_CACHEDRAW_DADDV3_1_H
#define CLASSES_ML_CACHEDRAW_DADDV3_1_H

#include "classes/ml/CacheDraw.h"

namespace ml { class DebDraw; }

namespace ml {
// table 0x7100B77168
class CacheDraw::DADDV3_1 {
public:
    virtual void flush(ml::DebDraw*);  // slot 0
};
}  // namespace ml

#endif
