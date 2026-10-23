#ifndef CLASSES_GF_GFINITPARAMBLADE_H
#define CLASSES_GF_GFINITPARAMBLADE_H

#include "classes/gf/GfInitParam.h"

namespace gf {
// table 0x7100B3FB48
class GfInitParamBlade : public ::gf::GfInitParam {
public:
    virtual bool isAllWeapon() const;  // slot 0
    unsigned char pad_90[0xA5 - 0x90];
    // set by GfEvtModelBlade's constructor for blade 0x451 before it makes the blade; not known yet
    bool pad_a5;
};
}  // namespace gf

#endif
