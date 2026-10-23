#ifndef CLASSES_GF_GFASSETSETUPEVENTBLADE_H
#define CLASSES_GF_GFASSETSETUPEVENTBLADE_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfAssetSetupBlade.h"

namespace gf { enum GfAssetType : int; }

namespace gf {
// table 0x7100B451E8
class GfAssetSetupEventBlade : public ::gf::GfAssetSetupBlade {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfAssetSetupEventBlade() {}  // slot 1
    virtual const char* getAssetCategoryName() const;  // slot 3
    virtual const char* getMdlFile(gf::GfAssetType type);  // slot 4
    virtual const char* getArcFile(gf::GfAssetType type);  // slot 5
    virtual const char* getRetargetMotFile(gf::GfAssetType type);  // slot 7
    virtual const char* getEvtMotFile(gf::GfAssetType type);  // slot 8
    virtual const char* getEvtStpFile(gf::GfAssetType type);  // slot 16
    virtual int getEvtMotSlot() const;  // slot 23
    virtual int getEvtStpSlot() const;  // slot 30
    virtual const char* getEvtPath() const;  // slot 34
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif
