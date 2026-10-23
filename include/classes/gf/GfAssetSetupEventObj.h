#ifndef CLASSES_GF_GFASSETSETUPEVENTOBJ_H
#define CLASSES_GF_GFASSETSETUPEVENTOBJ_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfAssetSetup.h"

namespace gf { class GF_ASSET_HANDLE; }
namespace gf { enum GfAssetType : int; }
namespace gf { class GfInitParamEventObj; }

namespace gf {
// table 0x7100B44B10
class GfAssetSetupEventObj : public ::gf::GfAssetSetup {
public:
    GfAssetSetupEventObj();
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfAssetSetupEventObj() {}  // slot 1
    virtual const char* getAssetCategoryName() const;  // slot 3
    virtual const char* getMdlFile(gf::GfAssetType type);  // slot 4
    virtual const char* getArcFile(gf::GfAssetType type);  // slot 5
    virtual const char* getEfpFile(gf::GfAssetType type);  // slot 11
    virtual const char* getEabFile(gf::GfAssetType type);  // slot 12
    virtual const char* getEfbFile(gf::GfAssetType type);  // slot 13
    virtual int getMdlSlot() const;  // slot 19
    virtual int getArcSlot() const;  // slot 20
    virtual int getEfpSlot() const;  // slot 26
    virtual int getEabSlot() const;  // slot 27
    virtual int getEfbSlot() const;  // slot 28
    virtual GfAssetType getAssetType() const;  // slot 39
    void setup(GF_ASSET_HANDLE* handle, const GfInitParamEventObj& param);
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif
