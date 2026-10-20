#ifndef CLASSES_ML_CACHEDRAW_DZWRITE_H
#define CLASSES_ML_CACHEDRAW_DZWRITE_H

#include "classes/ml/CacheDraw.h"

namespace ml { class DebDraw; }

namespace ml {
// table 0x7100B76F58
class CacheDraw::DZWRITE {
public:
    virtual void flush(ml::DebDraw*);  // slot 0
};
}  // namespace ml

#endif
