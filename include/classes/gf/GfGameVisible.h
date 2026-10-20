#ifndef CLASSES_GF_GFGAMEVISIBLE_H
#define CLASSES_GF_GFGAMEVISIBLE_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfGameVisible; }

namespace gf {
// table 0x7100B56AF0
class GfGameVisible : public ::mm::mtl::PtrSingleton< ::gf::GfGameVisible> {
public:
    virtual ~GfGameVisible();  // slot 0
};
}  // namespace gf

#endif
