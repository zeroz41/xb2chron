#ifndef CLASSES_GF_GFASSETSETUPEVENTDRIVER_H
#define CLASSES_GF_GFASSETSETUPEVENTDRIVER_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfAssetSetupDriver.h"

namespace gf { enum GfAssetType : int; }

namespace gf {
// table 0x7100B44DB0
class GfAssetSetupEventDriver : public ::gf::GfAssetSetupDriver {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfAssetSetupEventDriver() {}  // slot 1
    virtual const char* getAssetCategoryName() const;  // slot 3
    virtual const char* getEvtMotFile(gf::GfAssetType type);  // slot 8
    virtual const char* getEvtStpFile(gf::GfAssetType type);  // slot 16
    virtual int getEvtMotSlot() const;  // slot 23
    virtual int getEvtStpSlot() const;  // slot 30
    virtual const char* getEvtPath() const;  // slot 34
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif
