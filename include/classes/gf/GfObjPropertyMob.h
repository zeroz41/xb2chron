#ifndef CLASSES_GF_GFOBJPROPERTYMOB_H
#define CLASSES_GF_GFOBJPROPERTYMOB_H

#include "classes/gf/GfObjProperty.h"

namespace gf {
// table 0x7100B6A328; the property of an object of type 7 (GfObjProperty::create's, 0x90 bytes)
class GfObjPropertyMob : public ::gf::GfObjProperty {
public:
    explicit GfObjPropertyMob(GF_OBJ_HANDLE* handle) : GfObjProperty(handle) {}
    virtual ~GfObjPropertyMob() {}  // slot 0
};
}  // namespace gf

#endif
