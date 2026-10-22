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
    unsigned char pad_C0[0x1C0 - 0xC0];
};
}  // namespace gf

#endif
