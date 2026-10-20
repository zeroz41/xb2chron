#ifndef CLASSES_GF_GFGAMECOND_H
#define CLASSES_GF_GFGAMECOND_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfGameCond; }

namespace gf {
// table 0x7100B54758
class GfGameCond : public ::mm::mtl::PtrSingleton< ::gf::GfGameCond> {
public:
    virtual ~GfGameCond();  // slot 0
};
}  // namespace gf

#endif
