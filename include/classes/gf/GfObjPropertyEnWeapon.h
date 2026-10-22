#ifndef CLASSES_GF_GFOBJPROPERTYENWEAPON_H
#define CLASSES_GF_GFOBJPROPERTYENWEAPON_H

#include "classes/gf/GfObjProperty.h"

namespace gf {
// table 0x7100B6A3C8; the property of an object of type 12 (GfObjProperty::create's, 0x90 bytes)
class GfObjPropertyEnWeapon : public ::gf::GfObjProperty {
public:
    explicit GfObjPropertyEnWeapon(GF_OBJ_HANDLE* handle) : GfObjProperty(handle) {}
    virtual ~GfObjPropertyEnWeapon() {}  // slot 0
};
}  // namespace gf

#endif
