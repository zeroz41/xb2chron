#ifndef CLASSES_GF_GFASSETSETUPEVENTENEMY_H
#define CLASSES_GF_GFASSETSETUPEVENTENEMY_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfAssetSetupEnemy.h"

namespace gf { class GF_ASSET_HANDLE; }
namespace gf { enum GfAssetType : int; }
namespace gf { class GfInitParamEnemy; }

namespace gf {
// table 0x7100B454B8
class GfAssetSetupEventEnemy : public ::gf::GfAssetSetupEnemy {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfAssetSetupEventEnemy() {}  // slot 1
    virtual const char* getAssetCategoryName() const;  // slot 3
    virtual const char* getEvtMotFile(gf::GfAssetType type);  // slot 8
    virtual const char* getEvtStpFile(gf::GfAssetType type);  // slot 16
    virtual int getEvtMotSlot() const;  // slot 23
    virtual int getEvtStpSlot() const;  // slot 30
    virtual const char* getEvtPath() const;  // slot 34
    virtual void setup(gf::GF_ASSET_HANDLE*, gf::GfInitParamEnemy const&);  // slot 40
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif
