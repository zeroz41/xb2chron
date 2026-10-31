#ifndef CLASSES_ML_CACHEDRAW_DCLEAR_H
#define CLASSES_ML_CACHEDRAW_DCLEAR_H

#include "classes/ml/CacheDraw.h"

namespace ml { class DebDraw; }

namespace ml {
// table 0x7100B76E98
class CacheDraw::DCLEAR : public CacheDraw::CMD {
public:
    DCLEAR() : CMD(0x1, 0, sizeof(DCLEAR)) {}
    virtual void flush(ml::DebDraw*);  // slot 0

};
}  // namespace ml

#endif
