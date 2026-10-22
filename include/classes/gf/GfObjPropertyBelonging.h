#ifndef CLASSES_GF_GFOBJPROPERTYBELONGING_H
#define CLASSES_GF_GFOBJPROPERTYBELONGING_H

#include "classes/gf/GfObjProperty.h"

namespace gf {
// table 0x7100B6A3E8; the property of an object of type 13 (GfObjProperty::create's, 0x90 bytes)
class GfObjPropertyBelonging : public ::gf::GfObjProperty {
public:
    explicit GfObjPropertyBelonging(GF_OBJ_HANDLE* handle) : GfObjProperty(handle) {}
    virtual ~GfObjPropertyBelonging() {}  // slot 0
};
}  // namespace gf

#endif
