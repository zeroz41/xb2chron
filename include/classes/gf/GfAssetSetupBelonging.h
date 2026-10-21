#ifndef CLASSES_GF_GFASSETSETUPBELONGING_H
#define CLASSES_GF_GFASSETSETUPBELONGING_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfAssetSetup.h"

namespace gf { class GfAssetType; }

namespace gf {
// table 0x7100B446D8
class GfAssetSetupBelonging : public ::gf::GfAssetSetup {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfAssetSetupBelonging();  // slot 1
    virtual void getMdlFile(gf::GfAssetType);  // slot 4
    virtual void getArcFile(gf::GfAssetType);  // slot 5
    virtual void getMotFile(gf::GfAssetType);  // slot 6
    virtual void getMdlSlot() const;  // slot 19
    virtual void getArcSlot() const;  // slot 20
    virtual void getPath() const;  // slot 33
    virtual void getAssetType() const;  // slot 39
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif
