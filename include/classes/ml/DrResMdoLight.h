#ifndef CLASSES_ML_DRRESMDOLIGHT_H
#define CLASSES_ML_DRRESMDOLIGHT_H

namespace ml { class DrResEtcParams; }

namespace ml {
// table none (its derived classes')
class DrResMdoLight {
public:
    virtual ~DrResMdoLight();  // slot 0
    virtual void release() = 0;  // slot 2
    virtual void update() = 0;  // slot 3
    virtual void getAdder() = 0;  // slot 4
    virtual void lgtCall_col_r(float*, ml::DrResEtcParams*);  // slot 5
    virtual void lgtCall_col_g(float*, ml::DrResEtcParams*);  // slot 6
    virtual void lgtCall_col_b(float*, ml::DrResEtcParams*);  // slot 7
    virtual void lgtCall_col_inv(float*, ml::DrResEtcParams*);  // slot 8
};
}  // namespace ml

#endif
