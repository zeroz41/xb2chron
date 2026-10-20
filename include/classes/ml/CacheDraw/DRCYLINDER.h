#ifndef CLASSES_ML_CACHEDRAW_DRCYLINDER_H
#define CLASSES_ML_CACHEDRAW_DRCYLINDER_H

#include "classes/ml/CacheDraw.h"

namespace ml { class DebDraw; }

namespace ml {
// table 0x7100B77060
class CacheDraw::DRCYLINDER {
public:
    virtual void flush(ml::DebDraw*);  // slot 0
};
}  // namespace ml

#endif
