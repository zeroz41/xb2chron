#ifndef CLASSES_GF_GFASSETSETUPDRIVERFORUI_H
#define CLASSES_GF_GFASSETSETUPDRIVERFORUI_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfAssetSetupDriver.h"

namespace gf { class GF_ASSET_HANDLE; }
namespace gf { enum GfAssetType : int; }
namespace gf { class GfInitParamDriver; }

namespace gf {
// table 0x7100B45080
class GfAssetSetupDriverForUi : public ::gf::GfAssetSetupDriver {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfAssetSetupDriverForUi() {}  // slot 1
    virtual const char* getUiMotFile(gf::GfAssetType type);  // slot 10
    virtual const char* getUiStpFile(gf::GfAssetType type);  // slot 17
    virtual int getUiMotSlot() const;  // slot 25
    virtual int getUiStpSlot() const;  // slot 31
    virtual void setup(gf::GF_ASSET_HANDLE*, gf::GfInitParamDriver const&);  // slot 40
    virtual GfAssetType getAssetTypeEvtMot() const;  // slot 42
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif
