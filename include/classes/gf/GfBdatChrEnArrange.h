#ifndef CLASSES_GF_GFBDATCHRENARRANGE_H
#define CLASSES_GF_GFBDATCHRENARRANGE_H

#include "classes/gf/IDataBdat.h"
#include "classes/mm/mtl/PtrSingleton.h"

class CBdatWrapper;
namespace gf { class GfBdatChrEnArrange; }

namespace gf {
// table 0x7100B469E8; IDataBdat at 0x8 (GfDataBdat::initialize keeps it in its list)
class GfBdatChrEnArrange : public ::mm::mtl::PtrSingleton< ::gf::GfBdatChrEnArrange>, public ::gf::IDataBdat {
public:
    GfBdatChrEnArrange();
    virtual ~GfBdatChrEnArrange();  // slot 0
    virtual void bdatRefresh();  // slot 2
    unsigned int getChrEnArrangeStart() const;
    unsigned int getChrEnArrangeEnd() const;
    unsigned int getChrEnArrangeParamID(unsigned int arrange) const;  // the arrangement's GfBdatChrEnParam row
    // Table wrappers exposed by the range queries; names follow their accessors.
    CBdatWrapper* m_fpChrEnArrange;  // 0x10
    unsigned char pad_18[0x18];
};
}  // namespace gf

#endif
