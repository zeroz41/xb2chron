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
    DPERS(const mm::Mat44& mtx, float fovy, float aspect, float near, const mm::Vec3* eye)
        : CMD(0x3, 0, sizeof(DPERS)) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                m_mtx[i][j] = mtx.m[i][j];
            }
        }
        m_fovy = fovy;
        m_aspect = aspect;
        m_near = near;
        m_eye = na(eye == nullptr ? mm::Vec3::zero : *eye);
    }
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
