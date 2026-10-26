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
    unsigned char pad_91[0x12c - 0x91];
    // a blade id: GfGameEvent::fn_71002A1FFC gives blade 1011 its default weapon (GfBdatChrBl::getChrBlDefWeapon)
    // in event 10345
    unsigned int pad_12c;
    unsigned char pad_130[0x1e0 - 0x130];
    // set by setupBladeForEventRightCS and setupBladeForEventLeftCS
    bool pad_1e0;
    bool pad_1e1;
};
}  // namespace gf

#endif
