#ifndef CLASSES_ML_DRLIGHTOBJAMB_H
#define CLASSES_ML_DRLIGHTOBJAMB_H

#include "classes/ml/DrLightObj.h"

namespace ml {
// table 0x7100B7B558
class DrLightObjAmb : public ::ml::DrLightObj {
public:
    virtual ~DrLightObjAmb();  // slot 0

    unsigned char pad_30[0x10];  // setupLgt's array stride is 0x40
};
}  // namespace ml

#endif
