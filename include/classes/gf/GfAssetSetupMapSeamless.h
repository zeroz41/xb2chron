#ifndef CLASSES_GF_GFASSETSETUPMAPSEAMLESS_H
#define CLASSES_GF_GFASSETSETUPMAPSEAMLESS_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfAssetSetup.h"

namespace gf { class GF_ASSET_HANDLE; }
namespace gf { class GfAssetPack; }
namespace gf { enum GfAssetType : int; }
namespace gf { class GfInitParamMapSeamless; }

namespace gf {
// table 0x7100B44978
class GfAssetSetupMapSeamless : public ::gf::GfAssetSetup {
public:
    GfAssetSetupMapSeamless();
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfAssetSetupMapSeamless() {}  // slot 1
    virtual const char* getMdlFile(gf::GfAssetType type);  // slot 4
    virtual const char* getEfbFile(gf::GfAssetType type);  // slot 13
    virtual int getMdlSlot() const;  // slot 19
    virtual const char* getPath() const;  // slot 33
    // 3.0.1 passes the asset type the file getters take as a third argument (1.0.0's symbol has two)
    virtual void requestCoreResource(gf::GfAssetPack*, gf::GF_ASSET_HANDLE*, gf::GfAssetType);  // slot 38
    virtual GfAssetType getAssetType() const;  // slot 39
    virtual const char* getColFile(gf::GfAssetType type);  // slot 40
    virtual const char* getNaviFile(gf::GfAssetType type);  // slot 41
    virtual const char* getGIblFile(gf::GfAssetType type);  // slot 42
    virtual const char* getLIblFile(gf::GfAssetType type);  // slot 43
    virtual int getColSlot() const;  // slot 44
    virtual int getNaviSlot() const;  // slot 45
    virtual int getEpkSlot() const;  // slot 46
    virtual int getGIblSlot() const;  // slot 47
    virtual int getLIblSlot() const;  // slot 48
    void setup(GF_ASSET_HANDLE* handle, const GfInitParamMapSeamless& param);
    static mm::mtl::RTTI m_rtti;

    // the constructor clears these; what they hold is not known yet
    unsigned char pad_1fc;
    mm::mtl::FixStr<128> pad_200;
    mm::mtl::FixStr<128> pad_284;
};
}  // namespace gf

#endif
