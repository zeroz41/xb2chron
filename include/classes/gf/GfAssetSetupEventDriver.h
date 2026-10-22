#ifndef CLASSES_GF_GFASSETSETUPEVENTDRIVER_H
#define CLASSES_GF_GFASSETSETUPEVENTDRIVER_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfAssetSetupDriver.h"

namespace gf { class GfAssetType; }

namespace gf {
// table 0x7100B44DB0
class GfAssetSetupEventDriver : public ::gf::GfAssetSetupDriver {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfAssetSetupEventDriver() {}  // slot 1
    virtual void getAssetCategoryName() const;  // slot 3
    virtual void getEvtMotFile(gf::GfAssetType);  // slot 8
    virtual void getEvtStpFile(gf::GfAssetType);  // slot 16
    virtual void getEvtMotSlot() const;  // slot 23
    virtual void getEvtStpSlot() const;  // slot 30
    virtual void getEvtPath() const;  // slot 34
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif
