#ifndef CLASSES_GF_GFBDATMAPLIST_H
#define CLASSES_GF_GFBDATMAPLIST_H

#include "classes/gf/IDataBdat.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfBdatMaplist; }

namespace gf {
// table 0x7100B47070; IDataBdat at 0x8 (GfDataBdat::initialize keeps it in its list)
class GfBdatMaplist : public ::mm::mtl::PtrSingleton< ::gf::GfBdatMaplist>, public ::gf::IDataBdat {
public:
    GfBdatMaplist();
    virtual ~GfBdatMaplist();  // slot 0
    virtual void bdatRefresh();  // slot 2
    unsigned char pad_10[0x18];  // fields: size from GfDataBdat::initialize's allocation
};
}  // namespace gf

#endif
