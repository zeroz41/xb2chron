#ifndef CLASSES_GF_GFASSETSETUPUIOBJ_H
#define CLASSES_GF_GFASSETSETUPUIOBJ_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfAssetSetup.h"

namespace gf { class GF_ASSET_HANDLE; }
namespace gf { enum GfAssetType : int; }
namespace gf { class GfInitParamUiObj; }

namespace gf {
// table 0x7100B44C60
class GfAssetSetupUiObj : public ::gf::GfAssetSetup {
public:
    GfAssetSetupUiObj();
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfAssetSetupUiObj() {}  // slot 1
    virtual const char* getAssetCategoryName() const;  // slot 3
    virtual const char* getMdlFile(gf::GfAssetType type);  // slot 4
    virtual const char* getArcFile(gf::GfAssetType type);  // slot 5
    virtual int getMdlSlot() const;  // slot 19
    virtual int getArcSlot() const;  // slot 20
    virtual const char* getPath() const;  // slot 33
    virtual GfAssetType getAssetType() const;  // slot 39
    void setup(GF_ASSET_HANDLE* handle, const GfInitParamUiObj& param);
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif
