#ifndef CLASSES_GF_GFFIELDCOLLECT_H
#define CLASSES_GF_GFFIELDCOLLECT_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfFieldCollect; }

namespace gf {
// table 0x7100B51488
class GfFieldCollect : public ::mm::mtl::PtrSingleton< ::gf::GfFieldCollect> {
public:
    virtual ~GfFieldCollect();  // slot 0
};
}  // namespace gf

#endif
