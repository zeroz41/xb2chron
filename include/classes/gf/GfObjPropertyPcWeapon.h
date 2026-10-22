#ifndef CLASSES_GF_GFOBJPROPERTYPCWEAPON_H
#define CLASSES_GF_GFOBJPROPERTYPCWEAPON_H

#include "classes/gf/GfObjProperty.h"

namespace gf {
// table 0x7100B6A388; the property of an object of type 10 (GfObjProperty::create's, 0x90 bytes)
class GfObjPropertyPcWeapon : public ::gf::GfObjProperty {
public:
    explicit GfObjPropertyPcWeapon(GF_OBJ_HANDLE* handle) : GfObjProperty(handle) {}
    virtual ~GfObjPropertyPcWeapon() {}  // slot 0
};
}  // namespace gf

#endif
