#ifndef CLASSES_GF_GFASSETSETUPEVENTBLADE_H
#define CLASSES_GF_GFASSETSETUPEVENTBLADE_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfAssetSetupBlade.h"

namespace gf { enum GfAssetType : int; }

namespace gf {
// table 0x7100B451E8
class GfAssetSetupEventBlade : public ::gf::GfAssetSetupBlade {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfAssetSetupEventBlade() {}  // slot 1
    virtual void getAssetCategoryName() const;  // slot 3
    virtual void getMdlFile(gf::GfAssetType);  // slot 4
    virtual void getArcFile(gf::GfAssetType);  // slot 5
    virtual void getRetargetMotFile(gf::GfAssetType);  // slot 7
    virtual void getEvtMotFile(gf::GfAssetType);  // slot 8
    virtual void getEvtStpFile(gf::GfAssetType);  // slot 16
    virtual void getEvtMotSlot() const;  // slot 23
    virtual void getEvtStpSlot() const;  // slot 30
    virtual void getEvtPath() const;  // slot 34
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif
