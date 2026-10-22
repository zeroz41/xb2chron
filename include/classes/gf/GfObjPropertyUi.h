#ifndef CLASSES_GF_GFOBJPROPERTYUI_H
#define CLASSES_GF_GFOBJPROPERTYUI_H

#include "classes/gf/GfObjProperty.h"

namespace gf {
// table 0x7100B6A428; the property of an object of type 15 (GfObjProperty::create's, 0x90 bytes)
class GfObjPropertyUi : public ::gf::GfObjProperty {
public:
    explicit GfObjPropertyUi(GF_OBJ_HANDLE* handle) : GfObjProperty(handle) {}
    virtual ~GfObjPropertyUi() {}  // slot 0
};
}  // namespace gf

#endif
