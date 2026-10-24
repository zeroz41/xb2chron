#ifndef CLASSES_GF_GFINITPARAMFOBJ_H
#define CLASSES_GF_GFINITPARAMFOBJ_H

#include "classes/gf/GfInitParam.h"

namespace gf {
// table 0x7100B52930
class GfInitParamFobj : public ::gf::GfInitParam {
public:
    unsigned char pad_90[0x94 - 0x90];
    // createSetupParam formats "paramid%d" with it
    unsigned char pad_94;
};
}  // namespace gf

#endif
