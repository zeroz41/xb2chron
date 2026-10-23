#ifndef CLASSES_ML_DRLIGHTOBJPNT_H
#define CLASSES_ML_DRLIGHTOBJPNT_H

#include "classes/ml/DrLightObj.h"

namespace ml {
// table 0x7100B7B5A8
class DrLightObjPnt : public ::ml::DrLightObj {
public:
    virtual ~DrLightObjPnt();  // slot 0

    unsigned char pad_8[0x94];
    float m_size;  // 0x9C, set by DrEnvironmentAnim::envlgt_pnt_size (the name is not the original's)
    unsigned char pad_a0[0x10];
    float m_speIntensity;  // 0xB0, set by DrEnvironmentAnim::envlgt_pnt_spe_Intensity (the name is not the original's)
};
}  // namespace ml

#endif
