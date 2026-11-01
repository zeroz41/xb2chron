#ifndef CLASSES_ML_DRFOGOBJGBL_H
#define CLASSES_ML_DRFOGOBJGBL_H

#include "mm/Col3.h"

namespace ml {
// table 0x7100B7B508
class DrFogObjGbl {
public:
    virtual ~DrFogObjGbl();  // slot 0
    virtual void update();  // slot 2

    // Fields set by DrEnvironmentAnim::envfog_parm_<name>, list links as DrLightObj's (the names are not the original's).
    DrFogObjGbl* m_prev;  // 0x8
    DrFogObjGbl* m_next;  // 0x10, DrFogMan::releaseAll walks the list through it
    unsigned char pad_18[0x8];
    // 0x20..0x68: DrFogMan::update copies them from its first fog (the colours as whole Col3s)
    mm::Col3 m_color;  // 0x20
    mm::Col3 m_sideColor;  // 0x2C
    mm::Col3 m_sunColor;  // 0x38
    float m_near;  // 0x44
    float m_far;  // 0x48
    float m_str;  // 0x4C
    float m_parmA;  // 0x50
    float m_pow;  // 0x54
    float m_parmB[4];  // 0x58
};
}  // namespace ml

#endif
