#ifndef CLASSES_GF_GFASSETSETUPEVENTNPC_H
#define CLASSES_GF_GFASSETSETUPEVENTNPC_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfAssetSetupNpc.h"

namespace gf { class GF_ASSET_HANDLE; }
namespace gf { class GfAssetType; }
namespace gf { class GfInitParamNpc; }

namespace gf {
// table 0x7100B45628
class GfAssetSetupEventNpc : public ::gf::GfAssetSetupNpc {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfAssetSetupEventNpc();  // slot 1
    virtual void getAssetCategoryName() const;  // slot 3
    virtual void getMotFile(gf::GfAssetType);  // slot 6
    virtual void getEvtMotFile(gf::GfAssetType);  // slot 8
    virtual void getEvtStpFile(gf::GfAssetType);  // slot 16
    virtual void getEvtStpSlot() const;  // slot 30
    virtual void getAssetType() const;  // slot 39
    virtual void setup(gf::GF_ASSET_HANDLE*, gf::GfInitParamNpc const&);  // slot 40
    virtual void getAssetTypeMot() const;  // slot 41
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif
