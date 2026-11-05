#ifndef CLASSES_ML_DRLIGHTOBJAMB_H
#define CLASSES_ML_DRLIGHTOBJAMB_H

#include "classes/ml/DrLightObj.h"
#include "mm/Col3.h"

namespace ml {
// table 0x7100B7B558
class DrLightObjAmb : public ::ml::DrLightObj {
public:
    virtual ~DrLightObjAmb();  // slot 0

    // 0x30: DrLightMan::updateAmb copies the first live ambient light's colour into its m_ambColor (the name is
    // not the original's)
    mm::Col3 m_color;
    unsigned char pad_3c[0x4];  // setupLgt's array stride is 0x40
};
}  // namespace ml

#endif
