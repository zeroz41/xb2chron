#ifndef CLASSES_GF_GFINITPARAMBLADE_H
#define CLASSES_GF_GFINITPARAMBLADE_H

#include "classes/gf/GfInitParam.h"
#include "classes/gf/SubViewCamera.h"

namespace gf {
// table 0x7100B3FB48
class GfInitParamBlade : public ::gf::GfInitParam {
public:
    // a setup to use instead of the factory's own (the name is not the original's). A member of each kind,
    // not of GfInitParam: the copy assignments copy it with the kind's own fields, apart from the base's
    // (GfInitParamDriver::operator=, GfObjSetupBlade's constructor)
    GfAssetSetup* m_assetSetup;
    virtual bool isAllWeapon() const { return m_isAllWeapon; }  // slot 0
    void setupForParty(unsigned int objId, int arg, unsigned int bladeId, GF_OBJ_HANDLE* handle, bool flag);
    void setupForEvent(unsigned int bladeId, bool flag);
    void setupForUi(unsigned int bladeId, VIEWCAM camera);

    // inline: no copy of it exists (event::ModelObj::setupModel builds one on the stack)
    GfInitParamBlade() : GfInitParam(4) {
        m_assetSetup = nullptr;
        pad_90 = false;
        pad_91 = true;
        m_weaponId = 0;
        pad_98 = -1;
        m_isAllWeapon = false;
        pad_a0 = 0;
        pad_a4 = false;
        pad_a5 = false;
        pad_84 = 1;
        pad_82 = 1;
    }
    // setupForParty: 1, and its bool argument
    bool pad_90;
    bool pad_91;
    unsigned char pad_92[0x94 - 0x92];
    // the blade's weapon: GfEvtModelBlade::create sets blade 0x3F0's default (GfBdatChrBl::getChrBlDefWeapon) in
    // event 0x4A3A (the name is not the original's)
    unsigned int m_weaponId;
    // setupForParty's int argument
    int pad_98;
    // what isAllWeapon returns (the name is not the original's)
    bool m_isAllWeapon;
    unsigned char pad_9d[0xa0 - 0x9d];
    unsigned int pad_a0;
    // setupForEvent: blade 1001 and its bool argument
    bool pad_a4;
    // set by GfEvtModelBlade's constructor for blade 0x451 before it makes the blade; not known yet
    bool pad_a5;
};
}  // namespace gf

#endif
