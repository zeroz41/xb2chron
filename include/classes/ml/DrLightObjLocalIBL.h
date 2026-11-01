#ifndef CLASSES_ML_DRLIGHTOBJLOCALIBL_H
#define CLASSES_ML_DRLIGHTOBJLOCALIBL_H

#include "classes/ml/DrLightObj.h"
#include "mm/Vec3.h"

namespace ml {
// table 0x7100B7EE58
class DrLightObjLocalIBL : public ::ml::DrLightObj {
public:
    virtual ~DrLightObjLocalIBL();  // slot 0

    // DrEnvironmentObjLgt::callback_Chk_LocalIBL clip tests this sphere (the names are not the original's)
    unsigned char pad_30[0xE0];
    mm::Vec3 m_pos;  // 0x110
    float m_radius;  // 0x120
};
}  // namespace ml

#endif
