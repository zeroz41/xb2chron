#ifndef CLASSES_GF_GFASSETSETUPDRIVERFORUI_H
#define CLASSES_GF_GFASSETSETUPDRIVERFORUI_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfAssetSetupDriver.h"

namespace gf { class GF_ASSET_HANDLE; }
namespace gf { class GfAssetType; }
namespace gf { class GfInitParamDriver; }

namespace gf {
// table 0x7100B45080
class GfAssetSetupDriverForUi : public ::gf::GfAssetSetupDriver {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfAssetSetupDriverForUi() {}  // slot 1
    virtual void getUiMotFile(gf::GfAssetType);  // slot 10
    virtual void getUiStpFile(gf::GfAssetType);  // slot 17
    virtual void getUiMotSlot() const;  // slot 25
    virtual void getUiStpSlot() const;  // slot 31
    virtual void setup(gf::GF_ASSET_HANDLE*, gf::GfInitParamDriver const&);  // slot 40
    virtual void getAssetTypeEvtMot() const;  // slot 42
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif
