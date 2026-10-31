#ifndef CLASSES_ML_CACHEDRAW_DBEGIN_H
#define CLASSES_ML_CACHEDRAW_DBEGIN_H

#include "classes/ml/CacheDraw.h"

namespace ml { class DebDraw; }

namespace ml {
// table 0x7100B77108
class CacheDraw::DBEGIN : public CacheDraw::CMD {
public:
    DBEGIN(unsigned int prim, unsigned int param) : CMD(0x32, 0, sizeof(DBEGIN)), m_prim(prim), m_param(param) {}
    virtual void flush(ml::DebDraw*);  // slot 0

    unsigned int m_prim;  // 0x0C (the name is not the original's)
    unsigned int m_param;  // 0x10 (the name is not the original's)
};
}  // namespace ml

#endif
