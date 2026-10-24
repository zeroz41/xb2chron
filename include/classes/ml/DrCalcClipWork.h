#ifndef CLASSES_ML_DRCALCCLIPWORK_H
#define CLASSES_ML_DRCALCCLIPWORK_H

namespace mm { class Vec3; }

namespace ml {
// table none (its derived classes')
class DrCalcClipWork {
public:
    virtual bool clipTest(mm::Vec3 const&, float) const;  // slot 0
    virtual bool clipLineTest(mm::Vec3 const&, mm::Vec3 const&, float) const;  // slot 1
    virtual bool clipTest(float const*, float const*) const;  // slot 2
    virtual bool clipTest(mm::Vec3 const*, int) const;  // slot 3
    virtual bool clipTypeTest(mm::Vec3 const&, float) const;  // slot 4
    virtual void debugDraw();  // slot 5
};
}  // namespace ml

#endif
