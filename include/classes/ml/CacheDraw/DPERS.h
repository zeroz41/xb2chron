#ifndef CLASSES_ML_CACHEDRAW_DPERS_H
#define CLASSES_ML_CACHEDRAW_DPERS_H

#include "classes/ml/CacheDraw.h"
#include "mm/Mat44.h"
#include "mm/Vec3.h"
#include "mm/Vec3NA.h"

namespace ml { class DebDraw; }

namespace ml {
// table 0x7100B76EC8
class CacheDraw::DPERS : public CacheDraw::CMD {
public:
    // command 0x3, kind 0, 0x68 bytes (CacheDraw's queueing function is not written yet)
    virtual void flush(ml::DebDraw*);  // slot 0
    // the command keeps the matrix unaligned at 0x0C and hands DebDraw a mm::Mat44 view of it
    const mm::Mat44& mat() const { return reinterpret_cast<const mm::Mat44&>(m_mtx); }
    // the command keeps three floats unaligned and hands DebDraw a mm::Vec3 view of them
    static const mm::Vec3& vec(const mm::Vec3NA& v) { return reinterpret_cast<const mm::Vec3&>(v); }

    float m_mtx[4][4];  // 0x0C (the name is not the original's)
    float m_fovy;  // 0x4C (the name is not the original's)
    float m_aspect;  // 0x50 (the name is not the original's)
    float m_near;  // 0x54 (the name is not the original's)
    mm::Vec3NA m_eye;  // 0x58 (the name is not the original's)
};
}  // namespace ml

#endif
