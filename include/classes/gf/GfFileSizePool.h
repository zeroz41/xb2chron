#ifndef CLASSES_GF_GFFILESIZEPOOL_H
#define CLASSES_GF_GFFILESIZEPOOL_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfFileSizePool; }

namespace gf {
// table 0x7100B45938
class GfFileSizePool : public ::mm::mtl::PtrSingleton< ::gf::GfFileSizePool> {
public:
    virtual ~GfFileSizePool();  // slot 0
};
}  // namespace gf

#endif
