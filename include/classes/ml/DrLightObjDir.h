#ifndef CLASSES_ML_DRLIGHTOBJDIR_H
#define CLASSES_ML_DRLIGHTOBJDIR_H

#include "classes/ml/DrLightObj.h"

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

    unsigned char pad_30[0x60];
    // 0x90: 1.0.0's initDir sets 1.0f; update picks shadow cache flag 0x4 when it is above 0, else 0x20 (the name
    // is not the original's)
    float m_shadowRate;
    unsigned char pad_94[0xC];  // setupLgt's array stride is 0xA0
};
}  // namespace ml

#endif
