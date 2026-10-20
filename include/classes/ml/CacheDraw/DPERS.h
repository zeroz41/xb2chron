#ifndef CLASSES_ML_CACHEDRAW_DPERS_H
#define CLASSES_ML_CACHEDRAW_DPERS_H

#include "classes/ml/CacheDraw.h"

namespace ml { class DebDraw; }

namespace ml {
// table 0x7100B76EC8
class CacheDraw::DPERS {
public:
    virtual void flush(ml::DebDraw*);  // slot 0
};
}  // namespace ml

#endif
