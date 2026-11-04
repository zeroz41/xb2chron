#ifndef CLASSES_GF_GFINITPARAMWEAPON_H
#define CLASSES_GF_GFINITPARAMWEAPON_H

#include "classes/gf/GfInitParam.h"
#include "gf/GfAppend.h"
#include "classes/gf/GfAppendHandles.h"

namespace gf {
// table 0x7100B3FBC0
class GfInitParamWeapon : public ::gf::GfInitParam {
public:
    // a setup to use instead of the factory's own (the name is not the original's). A member of each kind,
    // not of GfInitParam: the copy assignments copy it with the kind's own fields, apart from the base's
    // (GfInitParamDriver::operator=, GfObjSetupBlade's constructor)
    GfAssetSetup* m_assetSetup;
    void setupForEvent(unsigned int driverId, unsigned int bladeId);
    void setupForEventBlade(unsigned int weaponId, GF_OBJ_HANDLE* handle);
    void setupBladeForEventRightCS(unsigned int bladeId);
    void setupBladeForEventLeftCS(unsigned int bladeId);

    // inline: no copy of it exists (event::ModelObj::setupModel builds one on the stack)
    GfInitParamWeapon()
        : GfInitParam(10, 6), m_assetSetup(nullptr), pad_90(false), pad_91(false), pad_94(-1), pad_98(),
          pad_120(reinterpret_cast<GF_OBJ_HANDLE*>(-1)), pad_128(0), pad_12c(0), pad_130(), pad_1e0(false),
          pad_1e1(false), pad_1e4(0), pad_1e8(false) {}

    // setupForEventBlade clears it
    bool pad_90;
    bool pad_91;
    unsigned char pad_92[0x94 - 0x92];
    int pad_94;
    GfAppend pad_98;
    GF_OBJ_HANDLE* pad_120;
    unsigned int pad_128;
    // a blade id: GfGameEvent::createWeapon gives blade 1011 its default weapon (GfBdatChrBl::getChrBlDefWeapon)
    // in event 10345
    unsigned int pad_12c;
    GfAppendHandles pad_130;
    // set by setupBladeForEventRightCS and setupBladeForEventLeftCS
    bool pad_1e0;
    bool pad_1e1;
    unsigned char pad_1e2[0x1e4 - 0x1e2];
    unsigned int pad_1e4;
    bool pad_1e8;
};
}  // namespace gf

#endif
