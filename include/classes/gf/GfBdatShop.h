#ifndef CLASSES_GF_GFBDATSHOP_H
#define CLASSES_GF_GFBDATSHOP_H

#include "classes/gf/IDataBdat.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfBdatShop; }

namespace gf {
// table 0x7100B47D20; IDataBdat at 0x8 (GfDataBdat::initialize keeps it in its list)
class GfBdatShop : public ::mm::mtl::PtrSingleton< ::gf::GfBdatShop>, public ::gf::IDataBdat {
public:
    GfBdatShop();
    virtual ~GfBdatShop();  // slot 0
    virtual void bdatRefresh();  // slot 2
    unsigned char pad_10[0x40];  // fields: size from GfDataBdat::initialize's allocation
};
}  // namespace gf

#endif
