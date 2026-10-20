#ifndef CLASSES_ML_CACHEDRAW_DRCONE_H
#define CLASSES_ML_CACHEDRAW_DRCONE_H

#include "classes/ml/CacheDraw.h"

namespace ml { class DebDraw; }

namespace ml {
// table 0x7100B77048
class CacheDraw::DRCONE {
public:
    virtual void flush(ml::DebDraw*);  // slot 0
};
}  // namespace ml

#endif
