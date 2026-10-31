#ifndef CLASSES_ML_CACHEDRAW_DRLINE_H
#define CLASSES_ML_CACHEDRAW_DRLINE_H

#include "classes/ml/CacheDraw.h"
#include "mm/Vec3.h"
#include "mm/Vec3NA.h"

namespace ml { class DebDraw; }

namespace ml {
// table 0x7100B770A8
class CacheDraw::DRLINE : public CacheDraw::CMD {
public:
    DRLINE(const mm::Vec3& start, const mm::Vec3& end) : CMD(0x2C, 2, sizeof(DRLINE)), m_start(na(start)), m_end(na(end)) {}
    virtual void flush(ml::DebDraw*);  // slot 0

    // the command keeps three floats unaligned (12-byte stride in its flush) and hands DebDraw::add a mm::Vec3 view of them
    static const mm::Vec3& vec(const mm::Vec3NA& v) { return reinterpret_cast<const mm::Vec3&>(v); }

    mm::Vec3NA m_start;  // 0x0C (the name is not the original's)
    mm::Vec3NA m_end;  // 0x18 (the name is not the original's)
};
}  // namespace ml

#endif
