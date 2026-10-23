#ifndef CLASSES_GF_GFBDATCOND_H
#define CLASSES_GF_GFBDATCOND_H

#include "classes/gf/IDataBdat.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfBdatCond; }

namespace gf {
// table 0x7100B46BA8; IDataBdat at 0x8 (GfDataBdat::initialize keeps it in its list)
class GfBdatCond : public ::mm::mtl::PtrSingleton< ::gf::GfBdatCond>, public ::gf::IDataBdat {
public:
    GfBdatCond();
    virtual ~GfBdatCond();  // slot 0
    virtual void bdatRefresh();  // slot 2
    void destroyFP();
    unsigned char pad_10[0x68];  // fields: size from GfDataBdat::initialize's allocation
};
}  // namespace gf

#endif
