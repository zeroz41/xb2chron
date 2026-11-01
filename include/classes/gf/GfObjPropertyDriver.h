#ifndef CLASSES_GF_GFOBJPROPERTYDRIVER_H
#define CLASSES_GF_GFOBJPROPERTYDRIVER_H

#include "classes/gf/GfObjProperty.h"
#include "classes/gf/GfObjPropertyCharacter.h"
#include "gf/GfTargetProperty.h"

namespace gf {
class GfObjPropertyDriver : public ::gf::GfObjProperty {
public:
    explicit GfObjPropertyDriver(GF_OBJ_HANDLE* handle);
    virtual ~GfObjPropertyDriver() {}  // slot 0

    GfObjPropertyCharacter m_characterPart;  // 0x88: m_character points at it
    TargetInfo m_targetPart;                 // 0xC0: m_target points at it (the name is not the original's)
    // cleared by the constructor's body
    unsigned long pad_190;
    unsigned long pad_198;
    unsigned int pad_1A0;
    unsigned char pad_1A4[0xC];
};
}  // namespace gf

#endif
