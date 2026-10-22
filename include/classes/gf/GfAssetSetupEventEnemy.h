#ifndef CLASSES_GF_GFASSETSETUPEVENTENEMY_H
#define CLASSES_GF_GFASSETSETUPEVENTENEMY_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfAssetSetupEnemy.h"

namespace gf { class GF_ASSET_HANDLE; }
namespace gf { class GfAssetType; }
namespace gf { class GfInitParamEnemy; }

namespace gf {
// table 0x7100B454B8
class GfAssetSetupEventEnemy : public ::gf::GfAssetSetupEnemy {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfAssetSetupEventEnemy() {}  // slot 1
    virtual void getAssetCategoryName() const;  // slot 3
    virtual void getEvtMotFile(gf::GfAssetType);  // slot 8
    virtual void getEvtStpFile(gf::GfAssetType);  // slot 16
    virtual void getEvtMotSlot() const;  // slot 23
    virtual void getEvtStpSlot() const;  // slot 30
    virtual void getEvtPath() const;  // slot 34
    virtual void setup(gf::GF_ASSET_HANDLE*, gf::GfInitParamEnemy const&);  // slot 40
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif
