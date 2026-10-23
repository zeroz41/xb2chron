#ifndef CLASSES_GF_GFASSETSETUPBELONGING_H
#define CLASSES_GF_GFASSETSETUPBELONGING_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfAssetSetup.h"
#include "gf/GfAppend.h"

namespace gf { class GF_ASSET_HANDLE; }
namespace gf { enum GfAssetType : int; }
namespace gf { class GfInitParamBelonging; }

namespace gf {
// table 0x7100B446D8
class GfAssetSetupBelonging : public ::gf::GfAssetSetup {
public:
    GfAssetSetupBelonging();
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfAssetSetupBelonging() {}  // slot 1
    virtual const char* getMdlFile(gf::GfAssetType type);  // slot 4
    virtual const char* getArcFile(gf::GfAssetType type);  // slot 5
    virtual const char* getMotFile(gf::GfAssetType type);  // slot 6
    virtual int getMdlSlot() const;  // slot 19
    virtual int getArcSlot() const;  // slot 20
    virtual const char* getPath() const;  // slot 33
    virtual GfAssetType getAssetType() const;  // slot 39
    void setup(GF_ASSET_HANDLE* handle, const GfInitParamBelonging& param);
    static mm::mtl::RTTI m_rtti;

    GfAppend m_append;  // the name is not the original's
};
}  // namespace gf

#endif
