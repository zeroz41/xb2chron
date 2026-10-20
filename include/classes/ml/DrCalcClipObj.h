#ifndef CLASSES_ML_DRCALCCLIPOBJ_H
#define CLASSES_ML_DRCALCCLIPOBJ_H

namespace mm { class Vec3; }

namespace ml {
// table none (its derived classes')
class DrCalcClipObj {
public:
    virtual ~DrCalcClipObj();  // slot 0
    virtual void clipcoli_box(unsigned char const*, mm::Vec3 const&);  // slot 2
};
}  // namespace ml

#endif
