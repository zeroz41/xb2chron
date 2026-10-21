#ifndef CLASSES_GF_GFFIELDLODCOLIANIM_COLIUSERDATA_H
#define CLASSES_GF_GFFIELDLODCOLIANIM_COLIUSERDATA_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfFieldLodColiAnim.h"

namespace gf {
// table 0x7100B51ED0
class GfFieldLodColiAnim::ColiUserData {
public:
    virtual const mm::mtl::RTTI* getRTTI() const;  // slot 0
};
}  // namespace gf

#endif
