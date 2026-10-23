#ifndef CLASSES_GF_GFBDATCHRDR_H
#define CLASSES_GF_GFBDATCHRDR_H

#include "classes/gf/IDataBdat.h"
#include "classes/mm/mtl/PtrSingleton.h"

class CBdatWrapper;
namespace gf { class GfBdatChrDr; }

namespace gf {
// table 0x7100B468F8; IDataBdat at 0x8 (GfDataBdat::initialize keeps it in its list)
class GfBdatChrDr : public ::mm::mtl::PtrSingleton< ::gf::GfBdatChrDr>, public ::gf::IDataBdat {
public:
    GfBdatChrDr();
    virtual ~GfBdatChrDr();  // slot 0
    virtual void bdatRefresh();  // slot 2
    unsigned int getChrDrStart() const;
    unsigned int getChrDrEnd() const;
    // Table wrappers exposed by the range queries; names follow their accessors.
    CBdatWrapper* m_fpChrDr;  // 0x10
    unsigned char pad_18[0x10];
    unsigned int getChrDrChestHeight(unsigned int) const;
    unsigned int getChrDrLandingHeight(unsigned int) const;
    unsigned int getChrDrStill(unsigned int) const;
    unsigned int getChrDrRace(unsigned int) const;
    unsigned int getChrDrFootStep(unsigned int) const;
    unsigned int getChrDrFootStepEffect(unsigned int) const;
    unsigned int getChrDrGender(unsigned int) const;
    unsigned int getChrDrOffsetID(unsigned int) const;
    const char* getChrDrCenterBone(unsigned int) const;
    const char* getChrDrCamBone(unsigned int) const;
    const char* getChrDrModel(unsigned int) const;
    const char* getChrDrMotion(unsigned int) const;
    const char* getChrDrDebugName(unsigned int) const;
    unsigned int getChrDrAiID(unsigned int) const;
    unsigned int getChrDrEyeRot(unsigned int) const;
};
}  // namespace gf

#endif
