#ifndef ML_DRRESMDOMAT_H
#define ML_DRRESMDOMAT_H

namespace ml {
// Only the fields DrMdoAnim's and DrMdoMat's material callbacks write are known (names are not the original's).
// 0x20 bytes: MdoWrkMatRes::m_pResMat is an array of them (DrMdlObj::getMaterialRes indexes it << 5).
class DrResMdoMat {
public:
    void setColor(float r, float g, float b, float a);
    void setAlpha(float);  // stores m_alpha
    void setName(const char* name);

    const char* m_name;  // 0x00, set by setName
    float m_color[3];  // 0x08, set by DrMdoAnim::animcall_MatColorR/G/B
    float m_alpha;  // 0x14, set by setAlpha
    unsigned char pad_18[0x8];
};
}  // namespace ml

#endif
