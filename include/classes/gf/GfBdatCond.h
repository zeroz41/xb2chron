#ifndef CLASSES_GF_GFBDATCOND_H
#define CLASSES_GF_GFBDATCOND_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfBdatCond; }

namespace gf {
// a base of gf::GfBdatCond no evidence names yet
class TUnk_B46BD0 {
public:
    virtual ~TUnk_B46BD0();
    virtual void bdatRefresh() = 0;
};
// table 0x7100B46BA8; base at 0x8 unknown (TUnk_B46BD0)
class GfBdatCond : public ::mm::mtl::PtrSingleton< ::gf::GfBdatCond>, public TUnk_B46BD0 {
public:
    virtual ~GfBdatCond();  // slot 0
    virtual void bdatRefresh();  // slot 2
};
}  // namespace gf

#endif
