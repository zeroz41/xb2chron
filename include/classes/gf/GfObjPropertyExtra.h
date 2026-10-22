#ifndef CLASSES_GF_GFOBJPROPERTYEXTRA_H
#define CLASSES_GF_GFOBJPROPERTYEXTRA_H

#include "classes/gf/GfObjProperty.h"

namespace gf {
// table 0x7100B6A408; the property of an object of type 14 (GfObjProperty::create's, 0x90 bytes)
class GfObjPropertyExtra : public ::gf::GfObjProperty {
public:
    explicit GfObjPropertyExtra(GF_OBJ_HANDLE* handle) : GfObjProperty(handle) {}
    virtual ~GfObjPropertyExtra() {}  // slot 0
};
}  // namespace gf

#endif
