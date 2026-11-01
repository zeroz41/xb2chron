#ifndef CLASSES_ML_DRCALCCLIPWORKCONE_H
#define CLASSES_ML_DRCALCCLIPWORKCONE_H

#include "classes/ml/DrCalcClipWork.h"
#include "mm/Vec3.h"

namespace ml {
// table 0x7100B7E9B8
class DrCalcClipWorkCone : public ::ml::DrCalcClipWork {
public:
    DrCalcClipWorkCone();
    ~DrCalcClipWorkCone();  // not virtual: no table slot; its owners' destructors call it
    virtual bool clipTest(mm::Vec3 const&, float) const;  // slot 0
    virtual int clipTypeTest(mm::Vec3 const&, float) const;  // slot 4
    virtual void debugDraw();  // slot 5
    void setConeWork(mm::Vec3 const& pos, mm::Vec3 const& dir, float angle, float length);
    // set by setConeWork (the field names are not the original's)
    mm::Vec3 m_pos;      // 0x10: apex
    mm::Vec3 m_dir;      // 0x20: axis direction
    mm::Vec3 m_axis;     // 0x30: dir * length
    float m_length;      // 0x40
    float m_angle;       // 0x44
    float m_cosHalf;     // 0x48: cosf(angle * 0.5)
    float m_sin;         // 0x4C: sinf(angle)
    float m_dirDotPos;   // 0x50: dir.dot(pos)
    unsigned char pad_54[0xC];
};
}  // namespace ml

#endif
