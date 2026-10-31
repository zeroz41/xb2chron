#ifndef CLASSES_ML_CACHEDRAW_DRARROW_CUBE_H
#define CLASSES_ML_CACHEDRAW_DRARROW_CUBE_H

#include "classes/ml/CacheDraw.h"
#include "mm/Vec3.h"
#include "mm/Vec3NA.h"

namespace ml { class DebDraw; }

namespace ml {
// table 0x7100B77000
class CacheDraw::DRARROW_CUBE : public CacheDraw::CMD {
public:
    DRARROW_CUBE(const mm::Vec3& start, const mm::Vec3& end) : CMD(0x1A, 2, sizeof(DRARROW_CUBE)), m_start(na(start)), m_end(na(end)) {}
    virtual void flush(ml::DebDraw*);  // slot 0
    // the command keeps three floats unaligned and hands DebDraw a mm::Vec3 view of them
    static const mm::Vec3& vec(const mm::Vec3NA& v) { return reinterpret_cast<const mm::Vec3&>(v); }

    mm::Vec3NA m_start;  // 0x0C (the name is not the original's)
    mm::Vec3NA m_end;  // 0x18 (the name is not the original's)
};
}  // namespace ml

#endif
