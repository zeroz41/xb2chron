#ifndef CLASSES_GF_GFASSETSETUP_H
#define CLASSES_GF_GFASSETSETUP_H

namespace gf { class GF_ASSET_HANDLE; }
namespace gf { class GfAssetPack; }
namespace gf { class GfAssetType; }

namespace gf {
// table 0x7100B43688
class GfAssetSetup {
public:
    virtual void getRTTI() const;  // slot 0
    virtual ~GfAssetSetup();  // slot 1
    virtual void getAssetCategoryName() const;  // slot 3
    virtual void getMdlFile(gf::GfAssetType);  // slot 4
    virtual void getArcFile(gf::GfAssetType);  // slot 5
    virtual void getMotFile(gf::GfAssetType);  // slot 6
    virtual void getRetargetMotFile(gf::GfAssetType);  // slot 7
    virtual void getEvtMotFile(gf::GfAssetType);  // slot 8
    virtual void getSalvageMotFile(gf::GfAssetType);  // slot 9
    virtual void getUiMotFile(gf::GfAssetType);  // slot 10
    virtual void getEfpFile(gf::GfAssetType);  // slot 11
    virtual void getEabFile(gf::GfAssetType);  // slot 12
    virtual void getEfbFile(gf::GfAssetType);  // slot 13
    virtual void getEfTailFile(gf::GfAssetType);  // slot 14
    virtual void getStpFile(gf::GfAssetType);  // slot 15
    virtual void getEvtStpFile(gf::GfAssetType);  // slot 16
    virtual void getUiStpFile(gf::GfAssetType);  // slot 17
    virtual void getSalvageStpFile(gf::GfAssetType);  // slot 18
    virtual void getMdlSlot() const;  // slot 19
    virtual void getArcSlot() const;  // slot 20
    virtual void getMotSlot() const;  // slot 21
    virtual void getRetargetMotSlot() const;  // slot 22
    virtual void getEvtMotSlot() const;  // slot 23
    virtual void getSalvageMotSlot() const;  // slot 24
    virtual void getUiMotSlot() const;  // slot 25
    virtual void getEfpSlot() const;  // slot 26
    virtual void getEabSlot() const;  // slot 27
    virtual void getEfbSlot() const;  // slot 28
    virtual void getStpSlot() const;  // slot 29
    virtual void getEvtStpSlot() const;  // slot 30
    virtual void getUiStpSlot() const;  // slot 31
    virtual void getSalvageStpSlot() const;  // slot 32
    virtual void getPath() const;  // slot 33
    virtual void getEvtPath() const;  // slot 34
    virtual void getEffPath() const;  // slot 35
    virtual void getStpPath() const;  // slot 36
    virtual void getSePackPath() const;  // slot 37
    virtual void requestCoreResource(gf::GfAssetPack*, gf::GF_ASSET_HANDLE*);  // slot 38
    virtual void getAssetType() const;  // slot 39
};
}  // namespace gf

#endif
