#ifndef CLASSES_GF_GFINITPARAMMOB_H
#define CLASSES_GF_GFINITPARAMMOB_H

#include "classes/gf/GfInitParam.h"

namespace gf {
// table 0x7100B69FA8
class GfInitParamMob : public ::gf::GfInitParam {
public:
    // a setup to use instead of the factory's own (the name is not the original's). A member of each kind,
    // not of GfInitParam: the copy assignments copy it with the kind's own fields, apart from the base's
    // (GfInitParamDriver::operator=, GfObjSetupBlade's constructor)
    GfAssetSetup* m_assetSetup;
    // inline: no copy of it exists (GfObjFactory's createGmkMob and createMobNull build it on the stack)
    GfInitParamMob() : GfInitParam(7), pad_90() {
        m_assetSetup = nullptr;
        pad_82 = 1;
    }

    // GfObjFactory::createGmkMob stores its four unsigned short arguments here; createMob passes them on to
    // the unnamed file-local helper of gf_obj_factory.cpp that sets up the mob's belongings (GfAppendUtil::setupBelonging)
    unsigned short pad_90[4];
};
}  // namespace gf

#endif
