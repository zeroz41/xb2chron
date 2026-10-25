#ifndef CLASSES_GF_GFOBJPROPERTYBLADE_H
#define CLASSES_GF_GFOBJPROPERTYBLADE_H

#include "classes/gf/GfObjProperty.h"
#include "classes/gf/GfObjPropertyCharacter.h"

namespace gf {
class GfObjPropertyBlade : public ::gf::GfObjProperty {
public:
    explicit GfObjPropertyBlade(GF_OBJ_HANDLE* handle);
    virtual ~GfObjPropertyBlade() {}  // slot 0

    GfObjPropertyCharacter m_characterPart;  // 0x88: m_character points at it
    unsigned char pad_C0[0x1A4 - 0xC0];
    // what GfMenuGfObjAdapter's update_BL_* show (the field names are not the original's)
    int m_kizuna;              // btl::Misc::GetKizunaStage's
    unsigned int m_specialLv;  // the special level reached
    float m_specialGauge;      // the next level's gauge, 0..1
    float m_changeRecast;      // 0..1
    unsigned int m_comboReady;  // bits 0 and 1: ready
    unsigned char pad_1B8[0x1C0 - 0x1B8];
};
}  // namespace gf

#endif
