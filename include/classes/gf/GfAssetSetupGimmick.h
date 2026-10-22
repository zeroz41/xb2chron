#ifndef CLASSES_GF_GFASSETSETUPGIMMICK_H
#define CLASSES_GF_GFASSETSETUPGIMMICK_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfAssetSetup.h"

namespace gf { class GF_ASSET_HANDLE; }
namespace gf { enum GfAssetType : int; }
namespace gf { class GfInitParamGimmick; }

namespace gf {
// table 0x7100B44048
class GfAssetSetupGimmick : public ::gf::GfAssetSetup {
public:
    GfAssetSetupGimmick();
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfAssetSetupGimmick() {}  // slot 1
    virtual void getMdlFile(gf::GfAssetType);  // slot 4
    virtual void getArcFile(gf::GfAssetType);  // slot 5
    virtual void getMotFile(gf::GfAssetType);  // slot 6
    virtual void getEfpFile(gf::GfAssetType);  // slot 11
    virtual void getEabFile(gf::GfAssetType);  // slot 12
    virtual void getEfbFile(gf::GfAssetType);  // slot 13
    virtual void getStpFile(gf::GfAssetType);  // slot 15
    virtual void getMdlSlot() const;  // slot 19
    virtual void getArcSlot() const;  // slot 20
    virtual void getMotSlot() const;  // slot 21
    virtual void getEfpSlot() const;  // slot 26
    virtual void getEabSlot() const;  // slot 27
    virtual void getEfbSlot() const;  // slot 28
    virtual void getStpSlot() const;  // slot 29
    virtual void getPath() const;  // slot 33
    virtual void getAssetType() const;  // slot 39
    void setup(GF_ASSET_HANDLE* handle, const GfInitParamGimmick& param);
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif
