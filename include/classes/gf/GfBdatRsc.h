#ifndef CLASSES_GF_GFBDATRSC_H
#define CLASSES_GF_GFBDATRSC_H

#include "classes/gf/IDataBdat.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfBdatRsc; }

namespace gf {
// table 0x7100B47288; IDataBdat at 0x8 (GfDataBdat::initialize keeps it in its list)
class GfBdatRsc : public ::mm::mtl::PtrSingleton< ::gf::GfBdatRsc>, public ::gf::IDataBdat {
public:
    GfBdatRsc();
    virtual ~GfBdatRsc();  // slot 0
    virtual void bdatRefresh();  // slot 2
    int getRSC_PcWpnMenuImageID(unsigned int rsc) const;  // a weapon resource's menu image
    unsigned char pad_10[0x98];  // fields: size from GfDataBdat::initialize's allocation
};
}  // namespace gf

#endif
