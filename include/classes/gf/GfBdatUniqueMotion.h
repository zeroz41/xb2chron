#ifndef CLASSES_GF_GFBDATUNIQUEMOTION_H
#define CLASSES_GF_GFBDATUNIQUEMOTION_H

#include "classes/fw/MessageObject.h"
#include "classes/gf/IDataBdat.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfBdatUniqueMotion; }

namespace gf {
// table 0x7100B47F28; IDataBdat at 0x8 (GfDataBdat::initialize keeps it in its list)
class GfBdatUniqueMotion : public ::mm::mtl::PtrSingleton< ::gf::GfBdatUniqueMotion>, public ::gf::IDataBdat, public ::fw::MessageObject {
public:
    GfBdatUniqueMotion();
    virtual ~GfBdatUniqueMotion();  // slot 0
    virtual void bdatRefresh();  // slot 2
    unsigned char pad_28[0x8];  // fields: size from GfDataBdat::initialize's allocation
};
}  // namespace gf

#endif
