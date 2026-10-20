#ifndef CLASSES_ML_CACHEDRAW_DZCOMP_H
#define CLASSES_ML_CACHEDRAW_DZCOMP_H

#include "classes/ml/CacheDraw.h"

namespace ml { class DebDraw; }

namespace ml {
// table 0x7100B76F40
class CacheDraw::DZCOMP {
public:
    virtual void flush(ml::DebDraw*);  // slot 0
};
}  // namespace ml

#endif
