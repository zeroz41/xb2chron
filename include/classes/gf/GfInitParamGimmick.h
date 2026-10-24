#ifndef CLASSES_GF_GFINITPARAMGIMMICK_H
#define CLASSES_GF_GFINITPARAMGIMMICK_H

#include "classes/gf/GfInitParam.h"

namespace gf {
// table 0x7100B69F80
class GfInitParamGimmick : public ::gf::GfInitParam {
public:
    // createSetupParam copies it into the setup
    void* pad_90;
};
}  // namespace gf

#endif
