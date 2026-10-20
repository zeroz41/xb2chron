#ifndef CLASSES_ML_CACHEDRAW_DFONT_FLUSH_H
#define CLASSES_ML_CACHEDRAW_DFONT_FLUSH_H

#include "classes/ml/CacheDraw.h"

namespace ml { class DebDraw; }

namespace ml {
// table 0x7100B77210
class CacheDraw::DFONT_FLUSH {
public:
    virtual void flush(ml::DebDraw*);  // slot 0
};
}  // namespace ml

#endif
