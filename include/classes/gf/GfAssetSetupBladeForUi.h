#ifndef CLASSES_GF_GFASSETSETUPBLADEFORUI_H
#define CLASSES_GF_GFASSETSETUPBLADEFORUI_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfAssetSetupBlade.h"

namespace gf { enum GfAssetType : int; }

namespace gf {
// table 0x7100B45350
class GfAssetSetupBladeForUi : public ::gf::GfAssetSetupBlade {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfAssetSetupBladeForUi() {}  // slot 1
    virtual const char* getUiMotFile(gf::GfAssetType type);  // slot 10
    virtual const char* getUiStpFile(gf::GfAssetType type);  // slot 17
    virtual int getUiMotSlot() const;  // slot 25
    virtual int getUiStpSlot() const;  // slot 31
    virtual GfAssetType getAssetType() const;  // slot 39
    virtual GfAssetType getAssetTypeMot() const;  // slot 40
    virtual GfAssetType getAssetTypeEventMot() const;  // slot 41
    virtual GfAssetType getAssetTypeEfb() const;  // slot 42
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif
