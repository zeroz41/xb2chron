#ifndef CLASSES_GF_GFASSETSETUPENEMY_H
#define CLASSES_GF_GFASSETSETUPENEMY_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfAssetSetup.h"

namespace gf { class GF_ASSET_HANDLE; }
namespace gf { enum GfAssetType : int; }
namespace gf { class GfInitParamEnemy; }

namespace gf {
// table 0x7100B43AA8
class GfAssetSetupEnemy : public ::gf::GfAssetSetup {
public:
    GfAssetSetupEnemy();
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfAssetSetupEnemy() {}  // slot 1
    virtual void getMdlFile(gf::GfAssetType);  // slot 4
    virtual void getArcFile(gf::GfAssetType);  // slot 5
    virtual void getMotFile(gf::GfAssetType);  // slot 6
    virtual void getRetargetMotFile(gf::GfAssetType);  // slot 7
    virtual void getEfpFile(gf::GfAssetType);  // slot 11
    virtual void getEabFile(gf::GfAssetType);  // slot 12
    virtual void getEfbFile(gf::GfAssetType);  // slot 13
    virtual void getStpFile(gf::GfAssetType);  // slot 15
    virtual void getMdlSlot() const;  // slot 19
    virtual void getArcSlot() const;  // slot 20
    virtual void getMotSlot() const;  // slot 21
    virtual void getRetargetMotSlot() const;  // slot 22
    virtual void getEfpSlot() const;  // slot 26
    virtual void getEabSlot() const;  // slot 27
    virtual void getEfbSlot() const;  // slot 28
    virtual void getStpSlot() const;  // slot 29
    virtual void getPath() const;  // slot 33
    virtual void getAssetType() const;  // slot 39
    virtual void setup(gf::GF_ASSET_HANDLE*, gf::GfInitParamEnemy const&);  // slot 40
    virtual void getAddMotSlot() const;  // slot 41
    virtual void getAssetTypeMot() const;  // slot 42
    virtual void getAssetTypeArc() const;  // slot 43
    static mm::mtl::RTTI m_rtti;

    unsigned char pad_200[0x8];
};
}  // namespace gf

#endif
