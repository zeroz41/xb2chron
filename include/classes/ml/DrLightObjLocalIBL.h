#ifndef CLASSES_ML_DRLIGHTOBJLOCALIBL_H
#define CLASSES_ML_DRLIGHTOBJLOCALIBL_H

#include "classes/ml/DrLightObj.h"
#include "mm/Vec3.h"

namespace grlib { class CGLibTextureBuffer; }

namespace ml {
// table 0x7100B7EE58
class DrLightObjLocalIBL : public ::ml::DrLightObj {
public:
    DrLightObjLocalIBL();
    virtual ~DrLightObjLocalIBL();  // slot 0

    mm::Vec3 pad_30;  // the constructor zeroes x, y and z
    // 0x40, DrEnvironmentObjLgt::callback_Ren2D_LocalIBL draws its six faces (the name is not the original's)
    grlib::CGLibTextureBuffer* m_cubeTex;
    // 0x48: setup stores the cube texture's mip count - 2 (at least 0) (the name is not the original's)
    int m_mipBias;
    unsigned char pad_4c[0xC4];
    // DrEnvironmentObjLgt::callback_Chk_LocalIBL clip tests this sphere (the names are not the original's)
    mm::Vec3 m_pos;  // 0x110
    float m_radius;  // 0x120
    // 0x124: setup copies a byte of the setting; 1: m_radius is the extent's x, 0: the extent's length (the
    // constructor sets 2; the name is not the original's)
    int m_shapeType;
    unsigned int pad_128;  // setup copies the setting's word at 0x14; the constructor clears it
    unsigned char pad_12c[0x94];
    int pad_1c0;  // setup copies a byte of the setting while its flag bit 6 is set; the constructor sets 2
    unsigned char pad_1c4[0x7C];
    const void* pad_240;  // setup copies the setting's pointer at 0xE8; the constructor clears it
    unsigned char pad_248[0x8];  // setupLgt's array stride is 0x250
};
}  // namespace ml

#endif
