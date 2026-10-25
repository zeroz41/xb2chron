#ifndef CLASSES_ML_CACHEDRAW_DADDV3_3_H
#define CLASSES_ML_CACHEDRAW_DADDV3_3_H

#include "classes/ml/CacheDraw.h"
#include "mm/Vec3.h"
#include "mm/Vec3NA.h"

namespace ml { class DebDraw; }

namespace ml {
// table 0x7100B77138
class CacheDraw::DADDV3_3 : public CacheDraw::CMD {
public:
    virtual void flush(ml::DebDraw*);  // slot 0

    // the command keeps three floats unaligned (12-byte stride in its flush) and hands DebDraw::add a mm::Vec3 view of them
    static const mm::Vec3& vec(const mm::Vec3NA& v) { return reinterpret_cast<const mm::Vec3&>(v); }

    mm::Vec3NA m_v0;  // 0x0C (the name is not the original's)
    mm::Vec3NA m_v1;  // 0x18 (the name is not the original's)
    mm::Vec3NA m_v2;  // 0x24 (the name is not the original's)
};
}  // namespace ml

#endif
