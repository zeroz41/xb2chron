#ifndef CLASSES_GF_GFBDATRSC_H
#define CLASSES_GF_GFBDATRSC_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfBdatRsc; }

namespace gf {
// a base of gf::GfBdatRsc no evidence names yet
class TUnk_B472B0 {
public:
    virtual ~TUnk_B472B0();
    virtual void bdatRefresh() = 0;
};
// table 0x7100B47288; base at 0x8 unknown (TUnk_B472B0)
class GfBdatRsc : public ::mm::mtl::PtrSingleton< ::gf::GfBdatRsc>, public TUnk_B472B0 {
public:
    virtual ~GfBdatRsc();  // slot 0
    virtual void bdatRefresh();  // slot 2
};
}  // namespace gf

#endif
