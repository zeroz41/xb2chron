#ifndef CLASSES_GF_GFOBJPROPERTYFOBJ_H
#define CLASSES_GF_GFOBJPROPERTYFOBJ_H

#include "classes/gf/GfObjProperty.h"

namespace gf {
// table 0x7100B6A368; the property of an object of type 9 (GfObjProperty::create's, 0x90 bytes)
class GfObjPropertyFobj : public ::gf::GfObjProperty {
public:
    explicit GfObjPropertyFobj(GF_OBJ_HANDLE* handle) : GfObjProperty(handle) {}
    virtual ~GfObjPropertyFobj() {}  // slot 0
};
}  // namespace gf

#endif
