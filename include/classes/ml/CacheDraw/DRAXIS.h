#ifndef CLASSES_ML_CACHEDRAW_DRAXIS_H
#define CLASSES_ML_CACHEDRAW_DRAXIS_H

#include "classes/ml/CacheDraw.h"

namespace ml { class DebDraw; }

namespace ml {
// table 0x7100B76FD0
class CacheDraw::DRAXIS {
public:
    virtual void flush(ml::DebDraw*);  // slot 0
};
}  // namespace ml

#endif
