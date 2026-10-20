#ifndef CLASSES_GF_GFFIELDTIME_H
#define CLASSES_GF_GFFIELDTIME_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfFieldTime; }

namespace gf {
// table 0x7100B52638
class GfFieldTime : public ::mm::mtl::PtrSingleton< ::gf::GfFieldTime> {
public:
    virtual ~GfFieldTime();  // slot 0
};
}  // namespace gf

#endif
