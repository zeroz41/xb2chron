#ifndef ML_DRRESMDOMAT_H
#define ML_DRRESMDOMAT_H

namespace ml {
// Only the fields DrMdoAnim's material callbacks write are known (names are not the original's).
class DrResMdoMat {
public:
    void setAlpha(float);  // stores m_alpha

    unsigned char pad_0[0x8];
    float m_color[3];  // 0x08, set by DrMdoAnim::animcall_MatColorR/G/B
    float m_alpha;  // 0x14, set by setAlpha
};
}  // namespace ml

#endif
