#ifndef ML_DRRESMDOLIGHT_H
#define ML_DRRESMDOLIGHT_H

namespace ml {
class DrResEtcParams;

// Only the light value callbacks and their table are declared so far.
class DrResMdoLight {
public:
    typedef void (*LgtValFunc)(float* value, DrResEtcParams* params);
    static void lgtCall_col_r(float* value, DrResEtcParams* params);
    static void lgtCall_col_g(float* value, DrResEtcParams* params);
    static void lgtCall_col_b(float* value, DrResEtcParams* params);
    static void lgtCall_col_inv(float* value, DrResEtcParams* params);

    static LgtValFunc s_pCallLgtVal[4];
};
}  // namespace ml

#endif
