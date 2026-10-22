#ifndef CLASSES_GF_GFOBJPROPERTYNPC_H
#define CLASSES_GF_GFOBJPROPERTYNPC_H

#include "classes/gf/GfObjProperty.h"

namespace gf {
// table 0x7100B6A308; the property of an object of type 6 (GfObjProperty::create's, 0x90 bytes)
class GfObjPropertyNpc : public ::gf::GfObjProperty {
public:
    explicit GfObjPropertyNpc(GF_OBJ_HANDLE* handle) : GfObjProperty(handle) {}
    virtual ~GfObjPropertyNpc() {}  // slot 0
};
}  // namespace gf

#endif
