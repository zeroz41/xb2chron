#ifndef CLASSES_GF_GFINITPARAMBLADE_H
#define CLASSES_GF_GFINITPARAMBLADE_H

#include "classes/gf/GfInitParam.h"

namespace gf {
// table 0x7100B3FB48
class GfInitParamBlade : public ::gf::GfInitParam {
public:
    virtual void isAllWeapon() const;  // slot 0
};
}  // namespace gf

#endif
