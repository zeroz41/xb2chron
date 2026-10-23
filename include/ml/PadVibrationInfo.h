#ifndef ML_PADVIBRATIONINFO_H
#define ML_PADVIBRATIONINFO_H

namespace ml {
// a pad vibration: its pattern and how it plays (fw::PadManager::playVibration takes one; the names are not the
// original's: the salvage states give a pattern and leave the rest as the constructor sets it)
class PadVibrationInfo {
public:
    PadVibrationInfo(int pattern) {
        m_mode = 3;
        m_scale0 = 1.0f;
        m_scale2 = 1.0f;
        m_scale1 = 1.0f;
        m_scale3 = 1.0f;
        m_pattern = pattern;
    }

    int m_pattern;
    int m_mode;
    float m_scale0;
    float m_scale1;
    float m_scale2;
    float m_scale3;
};
}  // namespace ml

#endif
