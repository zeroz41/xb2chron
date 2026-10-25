#ifndef CLASSES_ML_CACHEDRAW_DEND_H
#define CLASSES_ML_CACHEDRAW_DEND_H

#include "classes/ml/CacheDraw.h"

namespace ml { class DebDraw; }

namespace ml {
// table 0x7100B77120
class CacheDraw::DEND : public CacheDraw::CMD {
public:
    virtual void flush(ml::DebDraw*);  // slot 0
};
}  // namespace ml

#endif
