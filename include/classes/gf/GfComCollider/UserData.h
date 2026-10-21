#ifndef CLASSES_GF_GFCOMCOLLIDER_USERDATA_H
#define CLASSES_GF_GFCOMCOLLIDER_USERDATA_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfComCollider.h"

namespace gf {
// table 0x7100B66298
class GfComCollider::UserData {
public:
    virtual const mm::mtl::RTTI* getRTTI() const;  // slot 0
};
}  // namespace gf

#endif
