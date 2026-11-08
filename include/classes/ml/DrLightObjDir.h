#ifndef CLASSES_ML_DRLIGHTOBJDIR_H
#define CLASSES_ML_DRLIGHTOBJDIR_H

#include "classes/ml/DrLightObj.h"
#include "mm/Mat44.h"
#include "mm/Vec3.h"

namespace ml { class DrLightMan; }

namespace ml {
// table 0x7100B7B580
class DrLightObjDir : public ::ml::DrLightObj {
public:
    virtual ~DrLightObjDir();  // slot 0
    virtual void update(ml::DrLightMan*);  // slot 2

    // 1.0.0 has both out of line; 3.0.1 only inlines them into the destructor
    void releaseDir();
    void deleteDirShadow();
    // DrEnvironmentObjLgt::setupLgt's copy of the resource's matrix
    void setMat(const float* mtx);

    // the names below are not the original's
    mm::Mat44 m_mat;  // 0x30, setMat copies it whole
    mm::Vec3 m_dir;  // 0x70, setMat's -z axis, normalized
    unsigned char pad_80[0x10];
    // 0x90: 1.0.0's initDir sets 1.0f; update picks shadow cache flag 0x4 when it is above 0, else 0x20 (the name
    // is not the original's)
    float m_shadowRate;
    unsigned char pad_94[0xC];  // setupLgt's array stride is 0xA0
};
}  // namespace ml

#endif
