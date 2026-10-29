#ifndef CLASSES_ML_DRLIGHTOBJSPT_H
#define CLASSES_ML_DRLIGHTOBJSPT_H

#include "classes/ml/DrLightObj.h"

namespace mm { class Vec3; }
namespace mm { class Mat44; }

namespace ml {
// table 0x7100B7B5D0
class DrLightObjSpt : public ::ml::DrLightObj {
public:
    virtual ~DrLightObjSpt();  // slot 0


    // 1.0.0 has both out of line; 3.0.1 only inlines them into the destructor
    void releaseSpt();
    void deleteSptShadow();
    void setMat(const mm::Mat44& mtx);
    void setPos(const mm::Vec3& pos);

    unsigned char pad_30[0x8C];
    float m_angle;  // 0xBC, set by DrEnvironmentAnim::envlgt_spt_angle (the name is not the original's)
    float m_size;  // 0xC0, set by DrEnvironmentAnim::envlgt_spt_size (the name is not the original's)
    unsigned char pad_c4[0x10];
    float m_speIntensity;  // 0xD4, set by DrEnvironmentAnim::envlgt_spt_spe_Intensity (the name is not the original's)
};
}  // namespace ml

#endif
