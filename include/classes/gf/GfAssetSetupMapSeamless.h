#ifndef CLASSES_GF_GFASSETSETUPMAPSEAMLESS_H
#define CLASSES_GF_GFASSETSETUPMAPSEAMLESS_H

#include "classes/gf/GfAssetSetup.h"

namespace gf { class GF_ASSET_HANDLE; }
namespace gf { class GfAssetPack; }
namespace gf { class GfAssetType; }

namespace gf {
// table 0x7100B44978
class GfAssetSetupMapSeamless : public ::gf::GfAssetSetup {
public:
    virtual void getRTTI() const;  // slot 0
    virtual ~GfAssetSetupMapSeamless();  // slot 1
    virtual void getMdlFile(gf::GfAssetType);  // slot 4
    virtual void getEfbFile(gf::GfAssetType);  // slot 13
    virtual void getMdlSlot() const;  // slot 19
    virtual void getPath() const;  // slot 33
    virtual void requestCoreResource(gf::GfAssetPack*, gf::GF_ASSET_HANDLE*);  // slot 38
    virtual void getAssetType() const;  // slot 39
    virtual void getColFile(gf::GfAssetType);  // slot 40
    virtual void getNaviFile(gf::GfAssetType);  // slot 41
    virtual void getGIblFile(gf::GfAssetType);  // slot 42
    virtual void getLIblFile(gf::GfAssetType);  // slot 43
    virtual void getColSlot() const;  // slot 44
    virtual void getNaviSlot() const;  // slot 45
    virtual void getEpkSlot() const;  // slot 46
    virtual void getGIblSlot() const;  // slot 47
    virtual void getLIblSlot() const;  // slot 48
};
}  // namespace gf

#endif
