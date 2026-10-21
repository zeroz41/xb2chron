#ifndef CLASSES_GF_GFASSETSETUPWEAPONEVENTCS_H
#define CLASSES_GF_GFASSETSETUPWEAPONEVENTCS_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfAssetSetupWeapon.h"

namespace gf { class GfAssetType; }

namespace gf {
// table 0x7100B44438
class GfAssetSetupWeaponEventCS : public ::gf::GfAssetSetupWeapon {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfAssetSetupWeaponEventCS();  // slot 1
    virtual void getEvtMotFile(gf::GfAssetType);  // slot 8
    virtual void getEvtMotSlot() const;  // slot 23
    virtual void getEvtPath() const;  // slot 34
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif
