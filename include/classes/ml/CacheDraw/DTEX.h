#ifndef CLASSES_ML_CACHEDRAW_DTEX_H
#define CLASSES_ML_CACHEDRAW_DTEX_H

#include "classes/ml/CacheDraw.h"

namespace ml { class DebDraw; }

namespace ml {
// table 0x7100B76EF8
class CacheDraw::DTEX {
public:
    virtual void flush(ml::DebDraw*);  // slot 0
};
}  // namespace ml

#endif
