#ifndef CLASSES_GF_GFASSETSETUPBLADEFORUI_H
#define CLASSES_GF_GFASSETSETUPBLADEFORUI_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfAssetSetupBlade.h"

namespace gf { class GfAssetType; }

namespace gf {
// table 0x7100B45350
class GfAssetSetupBladeForUi : public ::gf::GfAssetSetupBlade {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfAssetSetupBladeForUi() {}  // slot 1
    virtual void getUiMotFile(gf::GfAssetType);  // slot 10
    virtual void getUiStpFile(gf::GfAssetType);  // slot 17
    virtual void getUiMotSlot() const;  // slot 25
    virtual void getUiStpSlot() const;  // slot 31
    virtual void getAssetType() const;  // slot 39
    virtual void getAssetTypeMot() const;  // slot 40
    virtual void getAssetTypeEventMot() const;  // slot 41
    virtual void getAssetTypeEfb() const;  // slot 42
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif
