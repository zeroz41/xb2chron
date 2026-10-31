#ifndef CLASSES_GF_GFINITPARAMUIOBJ_H
#define CLASSES_GF_GFINITPARAMUIOBJ_H

#include "classes/gf/GfInitParam.h"

namespace gf {
// table 0x7100B5F8F0
class GfInitParamUiObj : public ::gf::GfInitParam {
public:
    // a setup to use instead of the factory's own (the name is not the original's). A member of each kind,
    // not of GfInitParam: the copy assignments copy it with the kind's own fields, apart from the base's
    // (GfInitParamDriver::operator=, GfObjSetupBlade's constructor)
    GfAssetSetup* m_assetSetup;
};
}  // namespace gf

#endif
