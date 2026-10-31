#ifndef CLASSES_GF_GFINITPARAMMAPLODANIM_H
#define CLASSES_GF_GFINITPARAMMAPLODANIM_H

#include "classes/gf/GfInitParam.h"

namespace gf {
// table 0x7100B69F58
class GfInitParamMapLodAnim : public ::gf::GfInitParam {
public:
    // a setup to use instead of the factory's own (the name is not the original's). A member of each kind,
    // not of GfInitParam: the copy assignments copy it with the kind's own fields, apart from the base's
    // (GfInitParamDriver::operator=, GfObjSetupBlade's constructor)
    GfAssetSetup* m_assetSetup;
    // inline: no copy of it exists (GfObjFactory::createMapLodAnim builds it on the stack)
    GfInitParamMapLodAnim() : GfInitParam(1) {
        m_assetSetup = nullptr;
        pad_90[0] = 0;
        pad_110 = 0;
    }

    unsigned char pad_90[0x110 - 0x90];  // createMapLodAnim clears its first byte (a name?)
    int pad_110;
};
}  // namespace gf

#endif
