#ifndef CLASSES_GF_GFINITPARAMNPC_H
#define CLASSES_GF_GFINITPARAMNPC_H

#include "classes/gf/GfInitParam.h"

namespace gf {
// table 0x7100B3FB70
class GfInitParamNpc : public ::gf::GfInitParam {
public:
    unsigned char pad_90[0x98 - 0x90];
    // createSetupParam copies it into the setup
    void* pad_98;
};
}  // namespace gf

#endif
