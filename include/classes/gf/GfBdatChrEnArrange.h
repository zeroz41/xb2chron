#ifndef CLASSES_GF_GFBDATCHRENARRANGE_H
#define CLASSES_GF_GFBDATCHRENARRANGE_H

#include "classes/gf/IDataBdat.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfBdatChrEnArrange; }

namespace gf {
// table 0x7100B469E8; IDataBdat at 0x8 (GfDataBdat::initialize keeps it in its list)
class GfBdatChrEnArrange : public ::mm::mtl::PtrSingleton< ::gf::GfBdatChrEnArrange>, public ::gf::IDataBdat {
public:
    GfBdatChrEnArrange();
    virtual ~GfBdatChrEnArrange();  // slot 0
    virtual void bdatRefresh();  // slot 2
    unsigned char pad_10[0x20];  // fields: size from GfDataBdat::initialize's allocation
};
}  // namespace gf

#endif
