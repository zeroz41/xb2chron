#ifndef CLASSES_GF_GFASSETSETUPENWEAPON_H
#define CLASSES_GF_GFASSETSETUPENWEAPON_H

#include "classes/gf/GfAssetSetup.h"

namespace gf { class GfAssetType; }

namespace gf {
// table 0x7100B44588
class GfAssetSetupEnWeapon : public ::gf::GfAssetSetup {
public:
    virtual void getRTTI() const;  // slot 0
    virtual ~GfAssetSetupEnWeapon();  // slot 1
    virtual void getMdlFile(gf::GfAssetType);  // slot 4
    virtual void getArcFile(gf::GfAssetType);  // slot 5
    virtual void getMotFile(gf::GfAssetType);  // slot 6
    virtual void getEfpFile(gf::GfAssetType);  // slot 11
    virtual void getStpFile(gf::GfAssetType);  // slot 15
    virtual void getMdlSlot() const;  // slot 19
    virtual void getArcSlot() const;  // slot 20
    virtual void getMotSlot() const;  // slot 21
    virtual void getEfpSlot() const;  // slot 26
    virtual void getStpSlot() const;  // slot 29
    virtual void getPath() const;  // slot 33
    virtual void getAssetType() const;  // slot 39
};
}  // namespace gf

#endif
