#ifndef CLASSES_ML_DRLIGHTOBJLOCALIBL_H
#define CLASSES_ML_DRLIGHTOBJLOCALIBL_H

#include "classes/ml/DrLightObj.h"
#include "mm/Vec3.h"

namespace grlib { class CGLibTextureBuffer; }

namespace ml {
// table 0x7100B7EE58
class DrLightObjLocalIBL : public ::ml::DrLightObj {
public:
    virtual ~DrLightObjLocalIBL();  // slot 0

    // DrEnvironmentObjLgt::callback_Chk_LocalIBL clip tests this sphere (the names are not the original's)
    unsigned char pad_30[0x10];
    // 0x40, DrEnvironmentObjLgt::callback_Ren2D_LocalIBL draws its six faces (the name is not the original's)
    grlib::CGLibTextureBuffer* m_cubeTex;
    unsigned char pad_48[0xC8];
    mm::Vec3 m_pos;  // 0x110
    float m_radius;  // 0x120
    unsigned char pad_124[0x12C];  // setupLgt's array stride is 0x250
};
}  // namespace ml

#endif
