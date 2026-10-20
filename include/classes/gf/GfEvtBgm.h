#ifndef CLASSES_GF_GFEVTBGM_H
#define CLASSES_GF_GFEVTBGM_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfEvtBgm; }

namespace gf {
// table 0x7100B53AD0
class GfEvtBgm : public ::mm::mtl::PtrSingleton< ::gf::GfEvtBgm> {
public:
    virtual ~GfEvtBgm();  // slot 0
};
}  // namespace gf

#endif
