#ifndef CLASSES_GF_GFINITPARAMENWEAPON_H
#define CLASSES_GF_GFINITPARAMENWEAPON_H

#include "classes/gf/GfInitParam.h"

namespace gf {
// table 0x7100B69FD0
class GfInitParamEnWeapon : public ::gf::GfInitParam {
public:
    virtual void getEnArrangeID() const;  // slot 2
};
}  // namespace gf

#endif
