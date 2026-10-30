#ifndef CLASSES_GF_GFINITPARAMDRIVER_H
#define CLASSES_GF_GFINITPARAMDRIVER_H

#include "classes/gf/GfInitParam.h"
#include "mm/mtl/FixedVector.h"

namespace gf {
// table 0x7100B3FB20
class GfInitParamDriver : public ::gf::GfInitParam {
public:
    virtual bool isAllWeapon() const { return m_isAllWeapon; }  // slot 0
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it, and nothing in 3.0.1 calls it. A member
    // because it fills this class's fields (m_bladeId at 0x1AC) and sits among gf_obj_setup.cpp's driver and blade
    // code. What it does: creation type 3, object id driverId, pad_40 = 7, pad_81/pad_82 cleared, m_bladeId =
    // bladeId; when GfDataDriver::fn_710023F9A8(driverId) accepts the driver, m_bladeId becomes
    // GfDataBlade::fn_7100237B70(driverId, -1) instead.
    void fn_710054E050(unsigned int driverId, unsigned int bladeId);

    // inline: no copy of it exists (event::ModelObj::setupModel builds one on the stack)
    GfInitParamDriver() : GfInitParam(3), pad_98() {
        m_assetSetup = nullptr;
        pad_90 = 0;
        pad_1a0 = 0;
        m_isAllWeapon = false;
        pad_1a2 = false;
        pad_1a4 = 0;
        pad_1a8 = 1.0f;
        m_bladeId = 0;
        pad_84 = 1;
        pad_82 = 1;
    }

    // an element of pad_98: 0x100 bytes of elements; the split into four of 0x40 is not known (the name is not
    // the original's)
    struct Entry {
        unsigned char pad_0[0x40];
    };

    unsigned int pad_90;
    unsigned char pad_94[0x98 - 0x94];
    // emptied by the (implicit) destructor: ModelObj::setupModel clears its size after making the driver
    mm::mtl::FixedVector<Entry, 4> pad_98;
    unsigned char pad_1a0;
    // what isAllWeapon returns (the name is not the original's)
    bool m_isAllWeapon;
    // GfGameEvent::createDriver sets it for an event's driver unless GfGameManager::isInMetJIJI
    bool pad_1a2;
    unsigned char pad_1a3;
    unsigned int pad_1a4;
    float pad_1a8;
    // the driver's blade: GfEvtModelDriver keeps it, reading the driver's own when it is 0 (the name is not the
    // original's)
    unsigned int m_bladeId;
};
}  // namespace gf

#endif
