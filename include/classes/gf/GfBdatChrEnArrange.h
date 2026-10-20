#ifndef CLASSES_GF_GFBDATCHRENARRANGE_H
#define CLASSES_GF_GFBDATCHRENARRANGE_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfBdatChrEnArrange; }

namespace gf {
// a base of gf::GfBdatChrEnArrange no evidence names yet
class TUnk_B46A10 {
public:
    virtual ~TUnk_B46A10();
    virtual void bdatRefresh() = 0;
};
// table 0x7100B469E8; base at 0x8 unknown (TUnk_B46A10)
class GfBdatChrEnArrange : public ::mm::mtl::PtrSingleton< ::gf::GfBdatChrEnArrange>, public TUnk_B46A10 {
public:
    virtual ~GfBdatChrEnArrange();  // slot 0
    virtual void bdatRefresh();  // slot 2
};
}  // namespace gf

#endif
