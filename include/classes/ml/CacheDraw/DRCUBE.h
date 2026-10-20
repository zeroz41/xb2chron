#ifndef CLASSES_ML_CACHEDRAW_DRCUBE_H
#define CLASSES_ML_CACHEDRAW_DRCUBE_H

#include "classes/ml/CacheDraw.h"

namespace ml { class DebDraw; }

namespace ml {
// table 0x7100B76FA0
class CacheDraw::DRCUBE {
public:
    virtual void flush(ml::DebDraw*);  // slot 0
};
}  // namespace ml

#endif
