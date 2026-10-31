#ifndef CLASSES_GF_GFINITPARAMENWEAPON_H
#define CLASSES_GF_GFINITPARAMENWEAPON_H

#include "classes/gf/GfInitParam.h"
#include "gf/GfAppend.h"
#include "gf/GFATTACH.h"

namespace gf {
// table 0x7100B69FD0
class GfInitParamEnWeapon : public ::gf::GfInitParam {
public:
    // a setup to use instead of the factory's own (the name is not the original's). A member of each kind,
    // not of GfInitParam: the copy assignments copy it with the kind's own fields, apart from the base's
    // (GfInitParamDriver::operator=, GfObjSetupBlade's constructor)
    GfAssetSetup* m_assetSetup;
    virtual unsigned int getEnArrangeID() const;  // slot 2
    unsigned char pad_90[0x98 - 0x90];
    // the weapon's model: createSetupParam takes its getMountIndex()
    GfAppend m_append;
    // what getEnArrangeID returns (the name is not the original's)
    unsigned int m_enArrangeId;
    // the enemy GfObjFactory::createEnWeapon hands GfAppendUtil::setupEnemy (the name is not the original's)
    GF_OBJ_HANDLE* m_ownerHandle;
    // the mount point GfObjFactory::createEnWeapon hands GfAppendUtil's setups (the name is not the original's)
    GFATTACH m_attach;
};
}  // namespace gf

#endif
