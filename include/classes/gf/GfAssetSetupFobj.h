#ifndef CLASSES_GF_GFASSETSETUPFOBJ_H
#define CLASSES_GF_GFASSETSETUPFOBJ_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfAssetSetup.h"

namespace gf { class GF_ASSET_HANDLE; }
namespace gf { class GfAssetType; }
namespace gf { class GfInitParamFobj; }

namespace gf {
// table 0x7100B44198
class GfAssetSetupFobj : public ::gf::GfAssetSetup {
public:
    GfAssetSetupFobj();
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfAssetSetupFobj() {}  // slot 1
    virtual void getMdlFile(gf::GfAssetType);  // slot 4
    virtual void getEabFile(gf::GfAssetType);  // slot 12
    virtual void getMdlSlot() const;  // slot 19
    virtual void getEabSlot() const;  // slot 27
    virtual void getPath() const;  // slot 33
    virtual void getAssetType() const;  // slot 39
    void setup(GF_ASSET_HANDLE* handle, const GfInitParamFobj& param);
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif
