#ifndef CLASSES_GF_GFBDATRSC_H
#define CLASSES_GF_GFBDATRSC_H

#include "classes/gf/IDataBdat.h"
#include "classes/mm/mtl/PtrSingleton.h"

class CBdatWrapper;
namespace gf { class GfBdatRsc; }

namespace gf {
// table 0x7100B47288; IDataBdat at 0x8 (GfDataBdat::initialize keeps it in its list)
class GfBdatRsc : public ::mm::mtl::PtrSingleton< ::gf::GfBdatRsc>, public ::gf::IDataBdat {
public:
    GfBdatRsc();
    virtual ~GfBdatRsc();  // slot 0
    virtual void bdatRefresh();  // slot 2
    void destroyFP();
    unsigned int getFLD_actorSEStart() const;
    unsigned int getFLD_actorSEEnd() const;
    int getRSC_PcWpnMenuImageID(unsigned int rsc) const;  // a weapon resource's menu image
    // Table wrappers exposed by the range queries; names follow their accessors.
    unsigned char pad_10[0x80];
    CBdatWrapper* m_fpFLD_actorSE;  // 0x90
    unsigned char pad_98[0x10];
};
}  // namespace gf

#endif
