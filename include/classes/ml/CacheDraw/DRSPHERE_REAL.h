#ifndef CLASSES_ML_CACHEDRAW_DRSPHERE_REAL_H
#define CLASSES_ML_CACHEDRAW_DRSPHERE_REAL_H

#include "classes/ml/CacheDraw.h"

namespace ml { class DebDraw; }

namespace ml {
// table 0x7100B77018
class CacheDraw::DRSPHERE_REAL {
public:
    virtual void flush(ml::DebDraw*);  // slot 0
};
}  // namespace ml

#endif
