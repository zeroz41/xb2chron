#ifndef CLASSES_GF_GFOBJPROPERTYEVENT_H
#define CLASSES_GF_GFOBJPROPERTYEVENT_H

#include "classes/gf/GfObjProperty.h"

namespace gf {
// table 0x7100B6A3A8; the property of an object of type 11 (GfObjProperty::create's, 0x90 bytes)
class GfObjPropertyEvent : public ::gf::GfObjProperty {
public:
    explicit GfObjPropertyEvent(GF_OBJ_HANDLE* handle) : GfObjProperty(handle) {}
    virtual ~GfObjPropertyEvent() {}  // slot 0
};
}  // namespace gf

#endif
