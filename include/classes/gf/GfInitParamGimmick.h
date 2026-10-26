#ifndef CLASSES_GF_GFINITPARAMGIMMICK_H
#define CLASSES_GF_GFINITPARAMGIMMICK_H

#include "classes/gf/GfInitParam.h"

namespace gf {
// table 0x7100B69F80
class GfInitParamGimmick : public ::gf::GfInitParam {
public:
    // createSetupParam copies it into the setup; GfObjFactory::createGmkEvent puts its row's "name" here (a BDAT
    // string)
    void* pad_90;
    unsigned char pad_98;
};
}  // namespace gf

#endif
