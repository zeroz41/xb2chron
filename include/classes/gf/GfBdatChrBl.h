#ifndef CLASSES_GF_GFBDATCHRBL_H
#define CLASSES_GF_GFBDATCHRBL_H

#include "classes/gf/IDataBdat.h"
#include "classes/mm/mtl/PtrSingleton.h"

class CBdatWrapper;
namespace gf { class GfBdatChrBl; }

namespace gf {
// table 0x7100B46750; IDataBdat at 0x8 (GfDataBdat::initialize keeps it in its list)
class GfBdatChrBl : public ::mm::mtl::PtrSingleton< ::gf::GfBdatChrBl>, public ::gf::IDataBdat {
public:
    GfBdatChrBl();
    virtual ~GfBdatChrBl();  // slot 0
    virtual void bdatRefresh();  // slot 2
    unsigned int getChrBlStart() const;
    unsigned int getChrBlEnd() const;
    // Table wrappers exposed by the range queries; names follow their accessors.
    CBdatWrapper* m_fpChrBl;  // 0x10
};
}  // namespace gf

#endif
