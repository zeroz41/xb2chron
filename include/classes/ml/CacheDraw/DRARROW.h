#ifndef CLASSES_ML_CACHEDRAW_DRARROW_H
#define CLASSES_ML_CACHEDRAW_DRARROW_H

#include "classes/ml/CacheDraw.h"
#include "mm/Vec3.h"
#include "mm/Vec3NA.h"

namespace ml { class DebDraw; }

namespace ml {
// table 0x7100B76FE8
class CacheDraw::DRARROW : public CacheDraw::CMD {
public:
    DRARROW(const mm::Vec3& start, const mm::Vec3& end) : CMD(0x19, 2, sizeof(DRARROW)), m_start(na(start)), m_end(na(end)) {}
    virtual void flush(ml::DebDraw*);  // slot 0
    // the command keeps three floats unaligned and hands DebDraw a mm::Vec3 view of them
    static const mm::Vec3& vec(const mm::Vec3NA& v) { return reinterpret_cast<const mm::Vec3&>(v); }

    mm::Vec3NA m_start;  // 0x0C (the name is not the original's)
    mm::Vec3NA m_end;  // 0x18 (the name is not the original's)
};
}  // namespace ml

#endif
