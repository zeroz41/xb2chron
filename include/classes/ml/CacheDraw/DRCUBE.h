#ifndef CLASSES_ML_CACHEDRAW_DRCUBE_H
#define CLASSES_ML_CACHEDRAW_DRCUBE_H

#include "classes/ml/CacheDraw.h"
#include "mm/Vec3.h"
#include "mm/Vec3NA.h"

namespace ml { class DebDraw; }

namespace ml {
// table 0x7100B76FA0
class CacheDraw::DRCUBE : public CacheDraw::CMD {
public:
    DRCUBE(const mm::Vec3& min, const mm::Vec3& max) : CMD(0xF, 2, sizeof(DRCUBE)), m_min(na(min)), m_max(na(max)) {}
    virtual void flush(ml::DebDraw*);  // slot 0
    // the command keeps three floats unaligned and hands DebDraw a mm::Vec3 view of them
    static const mm::Vec3& vec(const mm::Vec3NA& v) { return reinterpret_cast<const mm::Vec3&>(v); }

    mm::Vec3NA m_min;  // 0x0C (the name is not the original's)
    mm::Vec3NA m_max;  // 0x18 (the name is not the original's)
};
}  // namespace ml

#endif
