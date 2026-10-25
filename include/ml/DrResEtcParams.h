#ifndef ML_DRRESETCPARAMS_H
#define ML_DRRESETCPARAMS_H

namespace ml {
// Only the field getParams returns is known.
class DrResEtcParams {
public:
    float getParams() const;
    void setParams(float value);
    void setPreParams(float value);
    void setInitParams(float value);

    // Field names are not the original's. setParams/setPreParams write the slot of DrMan::s_nDblStockIdx and set
    // its bit in m_flags (bit idx for m_value, bit 2 + idx for m_preValue).
    unsigned short m_flags;  // 0x00
    unsigned char pad_2[0x2];
    float m_value[2];        // 0x04
    float m_preValue[2];     // 0x0C
    float m_params;  // 0x14, returned by getParams (the name is not the original's)
};
}  // namespace ml

#endif
