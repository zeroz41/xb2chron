#ifndef CLASSES_GF_GFOBJPROPERTYDRIVER_H
#define CLASSES_GF_GFOBJPROPERTYDRIVER_H

#include "classes/gf/GfObjProperty.h"
#include "classes/gf/GfObjPropertyCharacter.h"

namespace gf {
class GfObjPropertyDriver : public ::gf::GfObjProperty {
public:
    explicit GfObjPropertyDriver(GF_OBJ_HANDLE* handle);
    virtual ~GfObjPropertyDriver() {}  // slot 0

    GfObjPropertyCharacter m_characterPart;  // 0x88: m_character points at it
    unsigned char pad_C0[0x1B0 - 0xC0];
};
}  // namespace gf

#endif
