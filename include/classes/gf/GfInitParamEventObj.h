#ifndef CLASSES_GF_GFINITPARAMEVENTOBJ_H
#define CLASSES_GF_GFINITPARAMEVENTOBJ_H

#include "classes/gf/GfInitParam.h"

namespace gf {
// table 0x7100B3FAF8
class GfInitParamEventObj : public ::gf::GfInitParam {
public:
    // a setup to use instead of the factory's own (the name is not the original's). A member of each kind,
    // not of GfInitParam: the copy assignments copy it with the kind's own fields, apart from the base's
    // (GfInitParamDriver::operator=, GfObjSetupBlade's constructor)
    GfAssetSetup* m_assetSetup;
    // inline: no copy of it exists (event::ModelObj::setupModel builds one on the stack)
    GfInitParamEventObj() : GfInitParam(11, 7) { m_assetSetup = nullptr; }
};
}  // namespace gf

#endif
