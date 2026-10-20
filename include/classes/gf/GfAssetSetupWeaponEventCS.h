// not proven yet: its table differs from the original's (word 5: _ZNK2gf18GfAssetSetupWeapon20getAssetCategoryNameEv where the original has _ZNK2gf12GfAssetSetup20getAssetCategoryNameEv)
#ifndef CLASSES_GF_GFASSETSETUPWEAPONEVENTCS_H
#define CLASSES_GF_GFASSETSETUPWEAPONEVENTCS_H

#include "classes/gf/GfAssetSetupWeapon.h"

namespace gf { class GfAssetType; }

namespace gf {
// table 0x7100B44438
class GfAssetSetupWeaponEventCS : public ::gf::GfAssetSetupWeapon {
public:
    virtual void getRTTI() const;  // slot 0
    virtual ~GfAssetSetupWeaponEventCS();  // slot 1
    virtual void getEvtMotFile(gf::GfAssetType);  // slot 8
    virtual void getEvtMotSlot() const;  // slot 23
    virtual void getEvtPath() const;  // slot 34
};
}  // namespace gf

#endif
