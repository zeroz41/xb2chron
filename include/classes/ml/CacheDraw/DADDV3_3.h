#ifndef CLASSES_ML_CACHEDRAW_DADDV3_3_H
#define CLASSES_ML_CACHEDRAW_DADDV3_3_H

#include "classes/ml/CacheDraw.h"

namespace ml { class DebDraw; }

namespace ml {
// table 0x7100B77138
class CacheDraw::DADDV3_3 {
public:
    virtual void flush(ml::DebDraw*);  // slot 0
};
}  // namespace ml

#endif
