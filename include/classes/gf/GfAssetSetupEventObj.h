#ifndef CLASSES_GF_GFASSETSETUPEVENTOBJ_H
#define CLASSES_GF_GFASSETSETUPEVENTOBJ_H

#include "classes/gf/GfAssetSetup.h"

namespace gf { class GfAssetType; }

namespace gf {
// table 0x7100B44B10
class GfAssetSetupEventObj : public ::gf::GfAssetSetup {
public:
    virtual void getRTTI() const;  // slot 0
    virtual ~GfAssetSetupEventObj();  // slot 1
    virtual void getAssetCategoryName() const;  // slot 3
    virtual void getMdlFile(gf::GfAssetType);  // slot 4
    virtual void getArcFile(gf::GfAssetType);  // slot 5
    virtual void getEfpFile(gf::GfAssetType);  // slot 11
    virtual void getEabFile(gf::GfAssetType);  // slot 12
    virtual void getEfbFile(gf::GfAssetType);  // slot 13
    virtual void getMdlSlot() const;  // slot 19
    virtual void getArcSlot() const;  // slot 20
    virtual void getEfpSlot() const;  // slot 26
    virtual void getEabSlot() const;  // slot 27
    virtual void getEfbSlot() const;  // slot 28
    virtual void getAssetType() const;  // slot 39
};
}  // namespace gf

#endif
