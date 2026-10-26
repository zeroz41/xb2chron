#ifndef CLASSES_GF_GFINITPARAMWEAPON_H
#define CLASSES_GF_GFINITPARAMWEAPON_H

#include "classes/gf/GfInitParam.h"

namespace gf {
// table 0x7100B3FBC0
class GfInitParamWeapon : public ::gf::GfInitParam {
public:
    void setupForEvent(unsigned int driverId, unsigned int bladeId);
    void setupForEventBlade(unsigned int weaponId, GF_OBJ_HANDLE* handle);
    void setupBladeForEventRightCS(unsigned int bladeId);
    void setupBladeForEventLeftCS(unsigned int bladeId);
    // setupForEventBlade clears it
    bool pad_90;
    unsigned char pad_91[0x1e0 - 0x91];
    // set by setupBladeForEventRightCS and setupBladeForEventLeftCS
    bool pad_1e0;
    bool pad_1e1;
};
}  // namespace gf

#endif
