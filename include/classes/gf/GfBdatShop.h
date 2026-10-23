#ifndef CLASSES_GF_GFBDATSHOP_H
#define CLASSES_GF_GFBDATSHOP_H

#include "classes/gf/IDataBdat.h"
#include "classes/mm/mtl/PtrSingleton.h"

class CBdatWrapper;
namespace gf { class GfBdatShop; }

namespace gf {
// table 0x7100B47D20; IDataBdat at 0x8 (GfDataBdat::initialize keeps it in its list)
class GfBdatShop : public ::mm::mtl::PtrSingleton< ::gf::GfBdatShop>, public ::gf::IDataBdat {
public:
    GfBdatShop();
    virtual ~GfBdatShop();  // slot 0
    virtual void bdatRefresh();  // slot 2
    void destroyFP();
    unsigned int getShopChangeTaskStart() const;
    unsigned int getShopChangeTaskEnd() const;
    unsigned int getMNU_EventTheaterStart() const;
    unsigned int getMNU_EventTheaterEnd() const;
    // Table wrappers exposed by the range queries; names follow their accessors.
    unsigned char pad_10[0x20];
    CBdatWrapper* m_fpShopChangeTask;  // 0x30
    unsigned char pad_38[0x8];
    CBdatWrapper* m_fpMNU_EventTheater;  // 0x40
    unsigned char pad_48[0x8];
};
}  // namespace gf

#endif
