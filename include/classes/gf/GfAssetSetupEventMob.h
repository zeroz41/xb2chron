#ifndef CLASSES_GF_GFASSETSETUPEVENTMOB_H
#define CLASSES_GF_GFASSETSETUPEVENTMOB_H

#include "classes/gf/GfAssetSetupMob.h"

namespace gf { class GF_ASSET_HANDLE; }
namespace gf { class GfAssetType; }
namespace gf { class GfInitParamMob; }

namespace gf {
// table 0x7100B45790
class GfAssetSetupEventMob : public ::gf::GfAssetSetupMob {
public:
    virtual void getRTTI() const;  // slot 0
    virtual ~GfAssetSetupEventMob();  // slot 1
    virtual void getAssetCategoryName() const;  // slot 3
    virtual void getEvtStpFile(gf::GfAssetType);  // slot 16
    virtual void getEvtStpSlot() const;  // slot 30
    virtual void getEvtPath() const;  // slot 34
    virtual void setup(gf::GF_ASSET_HANDLE*, gf::GfInitParamMob const&);  // slot 40
};
}  // namespace gf

#endif
