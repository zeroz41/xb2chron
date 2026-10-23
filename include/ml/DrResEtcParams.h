#ifndef ML_DRRESETCPARAMS_H
#define ML_DRRESETCPARAMS_H

namespace ml {
// Only the field getParams returns is known.
class DrResEtcParams {
public:
    float getParams() const;

    unsigned char pad_0[0x14];
    float m_params;  // 0x14, returned by getParams (the name is not the original's)
};
}  // namespace ml

#endif
