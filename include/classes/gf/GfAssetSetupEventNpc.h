#ifndef CLASSES_GF_GFASSETSETUPEVENTNPC_H
#define CLASSES_GF_GFASSETSETUPEVENTNPC_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfAssetSetupNpc.h"

namespace gf { class GF_ASSET_HANDLE; }
namespace gf { enum GfAssetType : int; }
namespace gf { class GfInitParamNpc; }

namespace gf {
// table 0x7100B45628
class GfAssetSetupEventNpc : public ::gf::GfAssetSetupNpc {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfAssetSetupEventNpc() {}  // slot 1
    virtual const char* getAssetCategoryName() const;  // slot 3
    virtual const char* getMotFile(gf::GfAssetType type);  // slot 6
    virtual const char* getEvtMotFile(gf::GfAssetType type);  // slot 8
    virtual const char* getEvtStpFile(gf::GfAssetType type);  // slot 16
    virtual int getEvtStpSlot() const;  // slot 30
    virtual GfAssetType getAssetType() const;  // slot 39
    virtual void setup(gf::GF_ASSET_HANDLE*, gf::GfInitParamNpc const&);  // slot 40
    virtual GfAssetType getAssetTypeMot() const;  // slot 41
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif
