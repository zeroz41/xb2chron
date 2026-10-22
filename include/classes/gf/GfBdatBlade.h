#ifndef CLASSES_GF_GFBDATBLADE_H
#define CLASSES_GF_GFBDATBLADE_H

#include "classes/gf/IDataBdat.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfBdatBlade; }

namespace gf {
// table 0x7100B46228; IDataBdat at 0x8 (GfDataBdat::initialize keeps it in its list)
class GfBdatBlade : public ::mm::mtl::PtrSingleton< ::gf::GfBdatBlade>, public ::gf::IDataBdat {
public:
    GfBdatBlade();
    virtual ~GfBdatBlade();  // slot 0
    virtual void bdatRefresh();  // slot 2
    unsigned char pad_10[0x80];  // fields: size from GfDataBdat::initialize's allocation
};
}  // namespace gf

#endif
