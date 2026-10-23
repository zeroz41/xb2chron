#ifndef CLASSES_GF_GFBDATCHRENPARAM_H
#define CLASSES_GF_GFBDATCHRENPARAM_H

#include "classes/gf/IDataBdat.h"
#include "classes/mm/mtl/PtrSingleton.h"

class CBdatWrapper;
namespace gf { class GfBdatChrEnParam; }

namespace gf {
// table 0x7100B46A58; IDataBdat at 0x8 (GfDataBdat::initialize keeps it in its list)
class GfBdatChrEnParam : public ::mm::mtl::PtrSingleton< ::gf::GfBdatChrEnParam>, public ::gf::IDataBdat {
public:
    GfBdatChrEnParam();
    virtual ~GfBdatChrEnParam();  // slot 0
    virtual void bdatRefresh();  // slot 2
    unsigned int getChrEnParamTableEnd() const;
    // Table wrappers exposed by the range queries; names follow their accessors.
    unsigned char pad_10[0x8];
    CBdatWrapper* m_fpChrEnParamTable;  // 0x18
    unsigned char pad_20[0x18];
};
}  // namespace gf

#endif
