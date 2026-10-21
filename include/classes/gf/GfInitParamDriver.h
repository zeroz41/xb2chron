#ifndef CLASSES_GF_GFINITPARAMDRIVER_H
#define CLASSES_GF_GFINITPARAMDRIVER_H

#include "classes/gf/GfInitParam.h"

namespace gf {
// table 0x7100B3FB20
class GfInitParamDriver : public ::gf::GfInitParam {
public:
    virtual bool isAllWeapon() const;  // slot 0
};
}  // namespace gf

#endif
