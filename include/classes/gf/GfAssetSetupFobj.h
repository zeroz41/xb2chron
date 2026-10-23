#ifndef CLASSES_GF_GFASSETSETUPFOBJ_H
#define CLASSES_GF_GFASSETSETUPFOBJ_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfAssetSetup.h"

namespace gf { class GF_ASSET_HANDLE; }
namespace gf { enum GfAssetType : int; }
namespace gf { class GfInitParamFobj; }

namespace gf {
// table 0x7100B44198
class GfAssetSetupFobj : public ::gf::GfAssetSetup {
public:
    GfAssetSetupFobj();
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfAssetSetupFobj() {}  // slot 1
    virtual const char* getMdlFile(gf::GfAssetType type);  // slot 4
    virtual const char* getEabFile(gf::GfAssetType type);  // slot 12
    virtual int getMdlSlot() const;  // slot 19
    virtual int getEabSlot() const;  // slot 27
    virtual const char* getPath() const;  // slot 33
    virtual GfAssetType getAssetType() const;  // slot 39
    void setup(GF_ASSET_HANDLE* handle, const GfInitParamFobj& param);
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif
