#ifndef CLASSES_ML_DRFOGOBJGBL_H
#define CLASSES_ML_DRFOGOBJGBL_H

namespace ml {
// table 0x7100B7B508
class DrFogObjGbl {
public:
    virtual ~DrFogObjGbl();  // slot 0
    virtual void update();  // slot 2

    // Fields set by DrEnvironmentAnim::envfog_parm_<name>, list links as DrLightObj's (the names are not the original's).
    DrFogObjGbl* m_prev;  // 0x8
    DrFogObjGbl* m_next;  // 0x10, DrFogMan::releaseAll walks the list through it
    unsigned char pad_18[0x2C];
    float m_near;  // 0x44
    float m_far;  // 0x48
    float m_str;  // 0x4C
    unsigned char pad_50[0x4];
    float m_pow;  // 0x54
};
}  // namespace ml

#endif
