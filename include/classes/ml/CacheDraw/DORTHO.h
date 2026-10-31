#ifndef CLASSES_ML_CACHEDRAW_DORTHO_H
#define CLASSES_ML_CACHEDRAW_DORTHO_H

#include "classes/ml/CacheDraw.h"

namespace ml { class DebDraw; }

namespace ml {
// table 0x7100B76EE0
class CacheDraw::DORTHO : public CacheDraw::CMD {
public:
    DORTHO() : CMD(0x4, 0, sizeof(DORTHO)) {}
    virtual void flush(ml::DebDraw*);  // slot 0

};
}  // namespace ml

#endif
