#ifndef CLASSES_ML_CACHEDRAW_DMAT_H
#define CLASSES_ML_CACHEDRAW_DMAT_H

#include "classes/ml/CacheDraw.h"

namespace ml { class DebDraw; }

namespace ml {
// table 0x7100B76EB0
class CacheDraw::DMAT {
public:
    virtual void flush(ml::DebDraw*);  // slot 0
};
}  // namespace ml

#endif
