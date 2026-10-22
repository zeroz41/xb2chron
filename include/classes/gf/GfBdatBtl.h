#ifndef CLASSES_GF_GFBDATBTL_H
#define CLASSES_GF_GFBDATBTL_H

#include "classes/gf/IDataBdat.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfBdatBtl; }

namespace gf {
// table 0x7100B462F8; IDataBdat at 0x8 (GfDataBdat::initialize keeps it in its list)
class GfBdatBtl : public ::mm::mtl::PtrSingleton< ::gf::GfBdatBtl>, public ::gf::IDataBdat {
public:
    GfBdatBtl();
    virtual ~GfBdatBtl();  // slot 0
    virtual void bdatRefresh();  // slot 2
    unsigned char pad_10[0xD8];  // fields: size from GfDataBdat::initialize's allocation
};
}  // namespace gf

#endif
