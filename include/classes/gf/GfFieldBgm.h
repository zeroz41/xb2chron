#ifndef CLASSES_GF_GFFIELDBGM_H
#define CLASSES_GF_GFFIELDBGM_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfFieldBgm; }

namespace gf {
// table 0x7100B511B8
class GfFieldBgm : public ::mm::mtl::PtrSingleton< ::gf::GfFieldBgm> {
public:
    virtual ~GfFieldBgm();  // slot 0
};
}  // namespace gf

#endif
