#ifndef CLASSES_GF_GFBDATBLADE_H
#define CLASSES_GF_GFBDATBLADE_H

#include "classes/gf/IDataBdat.h"
#include "classes/mm/mtl/PtrSingleton.h"

class CBdatWrapper;
namespace gf { class GfBdatBlade; }

namespace gf {
// table 0x7100B46228; IDataBdat at 0x8 (GfDataBdat::initialize keeps it in its list)
class GfBdatBlade : public ::mm::mtl::PtrSingleton< ::gf::GfBdatBlade>, public ::gf::IDataBdat {
public:
    GfBdatBlade();
    virtual ~GfBdatBlade();  // slot 0
    virtual void bdatRefresh();  // slot 2
    void destroyFP();
    unsigned int getNameListStart() const;
    unsigned int getNameListEnd() const;
    unsigned int getBLD_RareListStart() const;
    unsigned int getBLD_RareListEnd() const;
    // Table wrappers exposed by the range queries; names follow their accessors.
    unsigned char pad_10[0x20];
    CBdatWrapper* m_fpNameList;  // 0x30
    unsigned char pad_38[0x48];
    CBdatWrapper* m_fpBLD_RareList;  // 0x80
    unsigned char pad_88[0x8];
    unsigned int getBLD_IdeaNeedPoint(unsigned int level) const;
    unsigned int getNameListCategory(unsigned int blade) const;  // GfDataBlade::getCommonBladeName
};
}  // namespace gf

#endif
