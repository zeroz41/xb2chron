#ifndef CLASSES_GF_GFINITPARAMDRIVER_H
#define CLASSES_GF_GFINITPARAMDRIVER_H

#include "classes/gf/GfInitParam.h"

namespace gf {
// table 0x7100B3FB20
class GfInitParamDriver : public ::gf::GfInitParam {
public:
    virtual bool isAllWeapon() const;  // slot 0
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it, and nothing in 3.0.1 calls it. A member
    // because it fills this class's fields (m_bladeId at 0x1AC) and sits among gf_obj_setup.cpp's driver and blade
    // code. What it does: creation type 3, object id driverId, pad_40 = 7, pad_81/pad_82 cleared, m_bladeId =
    // bladeId; when GfDataDriver::fn_710023F9A8(driverId) accepts the driver, m_bladeId becomes
    // GfDataBlade::fn_7100237B70(driverId, -1) instead.
    void fn_710054E050(unsigned int driverId, unsigned int bladeId);
    unsigned char pad_90[0x1A2 - 0x90];
    // GfGameEvent::createDriver sets it for an event's driver unless GfGameManager::isInMetJIJI
    bool pad_1a2;
    unsigned char pad_1a3[0x1AC - 0x1A3];
    // the driver's blade: GfEvtModelDriver keeps it, reading the driver's own when it is 0 (the name is not the
    // original's)
    unsigned int m_bladeId;
};
}  // namespace gf

#endif
