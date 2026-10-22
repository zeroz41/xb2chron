#ifndef CLASSES_GF_GFBDATQUEST_H
#define CLASSES_GF_GFBDATQUEST_H

#include "classes/gf/IDataBdat.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfBdatQuest; }
namespace gf { class GfSetupParam; }

namespace gf {
// table 0x7100B47218; IDataBdat at 0x8 (GfDataBdat::initialize keeps it in its list)
class GfBdatQuest : public ::mm::mtl::PtrSingleton< ::gf::GfBdatQuest>, public ::gf::IDataBdat {
public:
    // 3.0.1 gives it GfDataBdat::initialize's setup parameters (1.0.0's takes none)
    GfBdatQuest(const GfSetupParam& param);
    virtual ~GfBdatQuest();  // slot 0
    virtual void bdatRefresh();  // slot 2
    unsigned char pad_10[0x150];  // fields: size from GfDataBdat::initialize's allocation
};
}  // namespace gf

#endif
