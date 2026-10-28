#ifndef CLASSES_GF_GFINITPARAMMAPSEAMLESS_H
#define CLASSES_GF_GFINITPARAMMAPSEAMLESS_H

#include "classes/gf/GfInitParam.h"

namespace gf {
// table 0x7100B6B7E0
class GfInitParamMapSeamless : public ::gf::GfInitParam {
public:
    // inline: no copy of it exists (SCOM_CREATE_MAP_OBJ::exec builds it on the stack)
    GfInitParamMapSeamless() : GfInitParam(1, 0) {
        m_assetSetup = nullptr;
        pad_90 = false;
        pad_98 = nullptr;
    }

    // createSetupParam stores the object id in the setup's pad_70 when it is set, in its pad_6c otherwise
    bool pad_90;
    unsigned char pad_91[0x98 - 0x91];
    // createSetupParam sets the setup's pad_74 when it is not null
    void* pad_98;
};
}  // namespace gf

#endif
