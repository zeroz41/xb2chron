#ifndef CLASSES_ML_CACHEDRAW_DTEX_H
#define CLASSES_ML_CACHEDRAW_DTEX_H

#include "classes/ml/CacheDraw.h"

namespace ml { class DebDraw; }
namespace grlib { class CGLibTextureBuffer; }

namespace ml {
// table 0x7100B76EF8
class CacheDraw::DTEX : public CacheDraw::CMD {
public:
    DTEX(grlib::CGLibTextureBuffer* tex) : CMD(0x5, 0, sizeof(DTEX)), m_tex(tex) {}
    virtual void flush(ml::DebDraw*);  // slot 0

    grlib::CGLibTextureBuffer* m_tex;  // 0x10 (the name is not the original's)
};
}  // namespace ml

#endif
