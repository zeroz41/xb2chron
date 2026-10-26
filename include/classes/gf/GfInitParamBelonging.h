#ifndef CLASSES_GF_GFINITPARAMBELONGING_H
#define CLASSES_GF_GFINITPARAMBELONGING_H

#include "classes/gf/GfInitParam.h"
#include "gf/GfAppend.h"

namespace gf {
// table 0x7100B69F30
class GfInitParamBelonging : public ::gf::GfInitParam {
public:
    // the model: createSetupParam takes its getMountIndex()
    GfAppend m_append;
    unsigned char pad_118[0x130 - 0x118];
    // whether the setup's pad_50 is 1.0f (else 0.0f; createSetupParam)
    bool pad_130;
};
}  // namespace gf

#endif
