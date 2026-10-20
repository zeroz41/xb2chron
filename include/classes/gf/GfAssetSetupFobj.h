#ifndef CLASSES_GF_GFASSETSETUPFOBJ_H
#define CLASSES_GF_GFASSETSETUPFOBJ_H

#include "classes/gf/GfAssetSetup.h"

namespace gf { class GfAssetType; }

namespace gf {
// table 0x7100B44198
class GfAssetSetupFobj : public ::gf::GfAssetSetup {
public:
    virtual void getRTTI() const;  // slot 0
    virtual ~GfAssetSetupFobj();  // slot 1
    virtual void getMdlFile(gf::GfAssetType);  // slot 4
    virtual void getEabFile(gf::GfAssetType);  // slot 12
    virtual void getMdlSlot() const;  // slot 19
    virtual void getEabSlot() const;  // slot 27
    virtual void getPath() const;  // slot 33
    virtual void getAssetType() const;  // slot 39
};
}  // namespace gf

#endif
