#ifndef CLASSES_GF_GFINITPARAMBLADE_H
#define CLASSES_GF_GFINITPARAMBLADE_H

#include "classes/gf/GfInitParam.h"
#include "classes/gf/SubViewCamera.h"

namespace gf {
// table 0x7100B3FB48
class GfInitParamBlade : public ::gf::GfInitParam {
public:
    virtual bool isAllWeapon() const;  // slot 0
    void setupForParty(unsigned int objId, int arg, unsigned int bladeId, GF_OBJ_HANDLE* handle, bool flag);
    void setupForEvent(unsigned int bladeId, bool flag);
    void setupForUi(unsigned int bladeId, VIEWCAM camera);
    // setupForParty: 1, and its bool argument
    bool pad_90;
    bool pad_91;
    unsigned char pad_92[0x94 - 0x92];
    // the blade's weapon: GfEvtModelBlade::create sets blade 0x3F0's default (GfBdatChrBl::getChrBlDefWeapon) in
    // event 0x4A3A (the name is not the original's)
    unsigned int m_weaponId;
    // setupForParty's int argument
    int pad_98;
    unsigned char pad_9c[0xa4 - 0x9c];
    // setupForEvent: blade 1001 and its bool argument
    bool pad_a4;
    // set by GfEvtModelBlade's constructor for blade 0x451 before it makes the blade; not known yet
    bool pad_a5;
};
}  // namespace gf

#endif
