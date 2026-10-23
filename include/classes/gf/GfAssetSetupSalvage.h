#ifndef CLASSES_GF_GFASSETSETUPSALVAGE_H
#define CLASSES_GF_GFASSETSETUPSALVAGE_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfAssetSetupDriver.h"

namespace gf { class GF_ASSET_HANDLE; }
namespace gf { enum GfAssetType : int; }
namespace gf { class GfInitParamDriver; }

namespace gf {
// table 0x7100B44F18
class GfAssetSetupSalvage : public ::gf::GfAssetSetupDriver {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfAssetSetupSalvage() {}  // slot 1
    virtual const char* getAssetCategoryName() const;  // slot 3
    virtual const char* getMdlFile(gf::GfAssetType type);  // slot 4
    virtual const char* getArcFile(gf::GfAssetType type);  // slot 5
    virtual const char* getSalvageMotFile(gf::GfAssetType type);  // slot 9
    virtual const char* getSalvageStpFile(gf::GfAssetType type);  // slot 18
    virtual int getSalvageMotSlot() const;  // slot 24
    virtual int getSalvageStpSlot() const;  // slot 32
    virtual void setup(gf::GF_ASSET_HANDLE*, gf::GfInitParamDriver const&);  // slot 40
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif
