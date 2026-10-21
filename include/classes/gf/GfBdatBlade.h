#ifndef CLASSES_GF_GFBDATBLADE_H
#define CLASSES_GF_GFBDATBLADE_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfBdatBlade; }

namespace gf {
// a base of gf::GfBdatBlade no evidence names yet
class TUnk_B46250 {
public:
    virtual ~TUnk_B46250();
    virtual void bdatRefresh() = 0;
};
// table 0x7100B46228; base at 0x8 unknown (TUnk_B46250)
class GfBdatBlade : public ::mm::mtl::PtrSingleton< ::gf::GfBdatBlade>, public TUnk_B46250 {
public:
    virtual ~GfBdatBlade();  // slot 0
    virtual void bdatRefresh();  // slot 2
};
}  // namespace gf

#endif
