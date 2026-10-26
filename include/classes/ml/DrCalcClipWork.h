#ifndef CLASSES_ML_DRCALCCLIPWORK_H
#define CLASSES_ML_DRCALCCLIPWORK_H

namespace mm { class Vec3; }

namespace ml {
// table none (its derived classes')
class DrCalcClipWork {
public:
    // every derived constructor stores 0 at 0x8 (DrCalcClipWorkCone's then stores 2): the base's
    DrCalcClipWork() : m_type(0) {}
    virtual bool clipTest(mm::Vec3 const&, float) const;  // slot 0
    virtual bool clipLineTest(mm::Vec3 const&, mm::Vec3 const&, float) const;  // slot 1
    virtual bool clipTest(float const*, float const*) const;  // slot 2
    virtual bool clipTest(mm::Vec3 const*, int) const;  // slot 3
    virtual bool clipTypeTest(mm::Vec3 const&, float) const;  // slot 4
    virtual void debugDraw();  // slot 5

    int m_type;  // 0x8: 0, DrCalcClipWorkCone 2 (the name is not the original's)
};
}  // namespace ml

#endif
