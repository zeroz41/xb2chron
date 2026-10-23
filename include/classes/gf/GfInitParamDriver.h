#ifndef CLASSES_GF_GFINITPARAMDRIVER_H
#define CLASSES_GF_GFINITPARAMDRIVER_H

#include "classes/gf/GfInitParam.h"

namespace gf {
// table 0x7100B3FB20
class GfInitParamDriver : public ::gf::GfInitParam {
public:
    virtual bool isAllWeapon() const;  // slot 0
    unsigned char pad_90[0x1AC - 0x90];
    // the driver's blade: GfEvtModelDriver keeps it, reading the driver's own when it is 0 (the name is not the
    // original's)
    unsigned int m_bladeId;
};
}  // namespace gf

#endif
