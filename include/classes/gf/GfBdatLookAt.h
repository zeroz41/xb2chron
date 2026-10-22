#ifndef CLASSES_GF_GFBDATLOOKAT_H
#define CLASSES_GF_GFBDATLOOKAT_H

#include "classes/fw/MessageObject.h"
#include "classes/gf/IDataBdat.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfBdatLookAt; }

namespace gf {
// table 0x7100B46FA8; IDataBdat at 0x8 (GfDataBdat::initialize keeps it in its list)
class GfBdatLookAt : public ::mm::mtl::PtrSingleton< ::gf::GfBdatLookAt>, public ::gf::IDataBdat, public ::fw::MessageObject {
public:
    GfBdatLookAt();
    virtual ~GfBdatLookAt();  // slot 0
    virtual void bdatRefresh();  // slot 2
    unsigned char pad_28[0x8];  // fields: size from GfDataBdat::initialize's allocation
};
}  // namespace gf

#endif
