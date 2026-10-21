#ifndef CLASSES_GF_GFBDATSHOP_H
#define CLASSES_GF_GFBDATSHOP_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfBdatShop; }

namespace gf {
// a base of gf::GfBdatShop no evidence names yet
class TUnk_B47D48 {
public:
    virtual ~TUnk_B47D48();
    virtual void bdatRefresh() = 0;
};
// table 0x7100B47D20; base at 0x8 unknown (TUnk_B47D48)
class GfBdatShop : public ::mm::mtl::PtrSingleton< ::gf::GfBdatShop>, public TUnk_B47D48 {
public:
    virtual ~GfBdatShop();  // slot 0
    virtual void bdatRefresh();  // slot 2
};
}  // namespace gf

#endif
