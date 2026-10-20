#ifndef CLASSES_GF_GFFIELDZONE_H
#define CLASSES_GF_GFFIELDZONE_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfFieldZone; }

namespace gf {
// table 0x7100B527B0
class GfFieldZone : public ::mm::mtl::PtrSingleton< ::gf::GfFieldZone> {
public:
    virtual ~GfFieldZone();  // slot 0
};
}  // namespace gf

#endif
