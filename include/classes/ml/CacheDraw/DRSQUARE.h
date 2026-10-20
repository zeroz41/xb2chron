#ifndef CLASSES_ML_CACHEDRAW_DRSQUARE_H
#define CLASSES_ML_CACHEDRAW_DRSQUARE_H

#include "classes/ml/CacheDraw.h"

namespace ml { class DebDraw; }

namespace ml {
// table 0x7100B77090
class CacheDraw::DRSQUARE {
public:
    virtual void flush(ml::DebDraw*);  // slot 0
};
}  // namespace ml

#endif
