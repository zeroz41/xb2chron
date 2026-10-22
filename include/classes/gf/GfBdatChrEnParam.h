#ifndef CLASSES_GF_GFBDATCHRENPARAM_H
#define CLASSES_GF_GFBDATCHRENPARAM_H

#include "classes/gf/IDataBdat.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfBdatChrEnParam; }

namespace gf {
// table 0x7100B46A58; IDataBdat at 0x8 (GfDataBdat::initialize keeps it in its list)
class GfBdatChrEnParam : public ::mm::mtl::PtrSingleton< ::gf::GfBdatChrEnParam>, public ::gf::IDataBdat {
public:
    GfBdatChrEnParam();
    virtual ~GfBdatChrEnParam();  // slot 0
    virtual void bdatRefresh();  // slot 2
    unsigned char pad_10[0x28];  // fields: size from GfDataBdat::initialize's allocation
};
}  // namespace gf

#endif
