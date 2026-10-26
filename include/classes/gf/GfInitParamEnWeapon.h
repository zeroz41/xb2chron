#ifndef CLASSES_GF_GFINITPARAMENWEAPON_H
#define CLASSES_GF_GFINITPARAMENWEAPON_H

#include "classes/gf/GfInitParam.h"
#include "gf/GfAppend.h"

namespace gf {
// table 0x7100B69FD0
class GfInitParamEnWeapon : public ::gf::GfInitParam {
public:
    virtual void getEnArrangeID() const;  // slot 2
    unsigned char pad_90[0x98 - 0x90];
    // the weapon's model: createSetupParam takes its getMountIndex()
    GfAppend m_append;
};
}  // namespace gf

#endif
