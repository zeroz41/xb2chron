#ifndef CLASSES_GF_GFOBJPROPERTYGIMMICK_H
#define CLASSES_GF_GFOBJPROPERTYGIMMICK_H

#include "classes/gf/GfObjProperty.h"

namespace gf {
// table 0x7100B6A348; the property of an object of type 8 (GfObjProperty::create's, 0x90 bytes)
class GfObjPropertyGimmick : public ::gf::GfObjProperty {
public:
    explicit GfObjPropertyGimmick(GF_OBJ_HANDLE* handle) : GfObjProperty(handle) {}
    virtual ~GfObjPropertyGimmick() {}  // slot 0
};
}  // namespace gf

#endif
