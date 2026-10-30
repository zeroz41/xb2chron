#ifndef CLASSES_ML_CACHEDRAW_DFONT_FLUSH_H
#define CLASSES_ML_CACHEDRAW_DFONT_FLUSH_H

#include "classes/ml/CacheDraw.h"

namespace ml { class DebDraw; }

namespace ml {
// table 0x7100B77210
class CacheDraw::DFONT_FLUSH : public CacheDraw::CMD {
public:
    virtual void flush(ml::DebDraw*);  // slot 0

    unsigned char m_on;  // 0x0C read as a byte, tested != 0 (the name is not the original's)
};
}  // namespace ml

#endif
