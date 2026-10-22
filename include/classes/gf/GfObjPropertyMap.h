#ifndef CLASSES_GF_GFOBJPROPERTYMAP_H
#define CLASSES_GF_GFOBJPROPERTYMAP_H

#include "classes/gf/GfObjProperty.h"

namespace gf {
// table 0x7100B6A268; the property of an object of type 1 (GfObjProperty::create's, 0x90 bytes)
class GfObjPropertyMap : public ::gf::GfObjProperty {
public:
    explicit GfObjPropertyMap(GF_OBJ_HANDLE* handle) : GfObjProperty(handle) {}
    virtual ~GfObjPropertyMap() {}  // slot 0
};
}  // namespace gf

#endif
