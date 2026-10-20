#ifndef CLASSES_GF_GFFIELDTBOX_H
#define CLASSES_GF_GFFIELDTBOX_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfFieldTbox; }

namespace gf {
// table 0x7100B525F8
class GfFieldTbox : public ::mm::mtl::PtrSingleton< ::gf::GfFieldTbox> {
public:
    virtual ~GfFieldTbox();  // slot 0
};
}  // namespace gf

#endif
