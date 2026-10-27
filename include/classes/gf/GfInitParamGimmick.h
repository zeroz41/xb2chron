#ifndef CLASSES_GF_GFINITPARAMGIMMICK_H
#define CLASSES_GF_GFINITPARAMGIMMICK_H

#include "classes/gf/GfInitParam.h"

namespace gf {
// table 0x7100B69F80
class GfInitParamGimmick : public ::gf::GfInitParam {
public:
    // inline: no copy of it exists (GfObjFactory's createGmk* build it on the stack)
    GfInitParamGimmick() : GfInitParam(8), pad_90(nullptr), pad_98(0) {
        m_assetSetup = nullptr;
        m_gimmickType = GimmickType(0);
    }

    // createSetupParam copies it into the setup; GfObjFactory::createGmkEvent puts its row's "name" here (a BDAT
    // string)
    void* pad_90;
    unsigned char pad_98;
};
}  // namespace gf

#endif
