#ifndef ML_DRRESMDOMAT_H
#define ML_DRRESMDOMAT_H

#include "mm/Col4.h"

namespace ml {
// Only the fields DrMdoAnim's and DrMdoMat's material callbacks write are known (names are not the original's).
// 0x20 bytes: MdoWrkMatRes::m_pResMat is an array of them (DrMdlObj::getMaterialRes indexes it << 5).
class DrResMdoMat {
public:
    void setColor(float r, float g, float b, float a);
    void setAlpha(float);  // stores m_alpha
    void setName(const char* name);
    // copies everything but the name (DrMdoNomClone::cloneMdlObj)
    DrResMdoMat& operator=(const DrResMdoMat& other);

    const char* m_name;  // 0x00, set by setName
    mm::Col4 m_color;  // 0x08, r/g/b set by DrMdoAnim::animcall_MatColorR/G/B, a by setAlpha; operator= copies it as one
    // 0x18, operator= copies it; DrMdoSetup::unimate_alphaInfo writes it as the alpha info's second value (the
    // name is not the original's)
    float m_alphaParam;
    unsigned int pad_1C;  // 0x1C, operator= copies it
};
}  // namespace ml

#endif
