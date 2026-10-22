#ifndef CLASSES_GF_GFBDATITEM_H
#define CLASSES_GF_GFBDATITEM_H

#include "classes/gf/IDataBdat.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfBdatItem; }

namespace gf {
// table 0x7100B46D30; IDataBdat at 0x8 (GfDataBdat::initialize keeps it in its list)
class GfBdatItem : public ::mm::mtl::PtrSingleton< ::gf::GfBdatItem>, public ::gf::IDataBdat {
public:
    GfBdatItem();
    virtual ~GfBdatItem();  // slot 0
    virtual void bdatRefresh();  // slot 2
    unsigned char pad_10[0xD0];  // fields: size from GfDataBdat::initialize's allocation
};
}  // namespace gf

#endif
