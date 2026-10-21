#ifndef CLASSES_ML_DRCALCCLIPWORK_H
#define CLASSES_ML_DRCALCCLIPWORK_H

namespace mm { class Vec3; }

namespace ml {
// table none (its derived classes')
class DrCalcClipWork {
public:
    virtual void clipTest(mm::Vec3 const&, float) const;  // slot 0
    virtual void clipLineTest(mm::Vec3 const&, mm::Vec3 const&, float) const;  // slot 1
    virtual void clipTest(float const*, float const*) const;  // slot 2
    virtual void clipTest(mm::Vec3 const*, int) const;  // slot 3
    virtual bool clipTypeTest(mm::Vec3 const&, float) const { return false; }  // slot 4
    virtual void debugDraw() {}  // slot 5
};
}  // namespace ml

#endif
