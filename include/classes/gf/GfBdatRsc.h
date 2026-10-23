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
    const char* getRscMobListModel(unsigned int mob) const;
    const char* getRscEnModel(unsigned int rsc) const;
    const char* getRscEnMotion(unsigned int rsc) const;
    const char* getRscEnComp_Eff(unsigned int rsc) const;
    const char* getRscEnRotateBone(unsigned int rsc) const;
    const char* getRscEnCenterBone(unsigned int rsc) const;
    const char* getRscEnCamBone(unsigned int rsc) const;
    unsigned int getRscEnEyeRot(unsigned int rsc) const;
    unsigned int getRscEnFootStep(unsigned int rsc) const;
    unsigned int getRscEnFootStepEffect(unsigned int rsc) const;
    unsigned int getRscEnChestHeight(unsigned int rsc) const;
    unsigned int getRscEnoffsetID(unsigned int rsc) const;
    int getRscEnGoldDivideRev(unsigned int rsc) const;
    const char* getRscMobListMotion(unsigned int mob) const;
    unsigned int getRscMobListOffsetID(unsigned int mob) const;
    unsigned int getRscMobListExtraParts(unsigned int mob, unsigned int part) const;
    const char* getRSC_TboxListModel(unsigned int tbox) const;
    const char* getRSC_TboxListMotion(unsigned int tbox) const;
    const char* getRSC_MapObjListModel(unsigned int obj) const;
    const char* getRSC_MapObjListMotion(unsigned int obj) const;
    unsigned int getRSC_MapObjListExtraParts1(unsigned int obj) const;
    // Table wrappers exposed by the range queries; names follow their accessors.
    unsigned char pad_10[0x80];
    CBdatWrapper* m_fpFLD_actorSE;  // 0x90
    unsigned char pad_98[0x10];
};
}  // namespace gf

#endif
