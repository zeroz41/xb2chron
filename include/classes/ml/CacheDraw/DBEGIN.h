#ifndef CLASSES_ML_CACHEDRAW_DBEGIN_H
#define CLASSES_ML_CACHEDRAW_DBEGIN_H

#include "classes/ml/CacheDraw.h"

namespace ml { class DebDraw; }

namespace ml {
// table 0x7100B77108
class CacheDraw::DBEGIN {
public:
    virtual void flush(ml::DebDraw*);  // slot 0
};
}  // namespace ml

#endif
