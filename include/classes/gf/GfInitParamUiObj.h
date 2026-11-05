#ifndef CLASSES_GF_GFINITPARAMUIOBJ_H
#define CLASSES_GF_GFINITPARAMUIOBJ_H

#include "classes/gf/GfInitParam.h"

namespace gf {
// table 0x7100B5F8F0
class GfInitParamUiObj : public ::gf::GfInitParam {
public:
    // inline: no copy of it exists (GfMenuModelView::addMapObjObject builds one on the stack: kind 15, pad_40 10, the setup
    // cleared; this unit emits the table)
    GfInitParamUiObj() : GfInitParam(15, 10) { m_assetSetup = nullptr; }

    // a setup to use instead of the factory's own (the name is not the original's). A member of each kind,
    // not of GfInitParam: the copy assignments copy it with the kind's own fields, apart from the base's
    // (GfInitParamDriver::operator=, GfObjSetupBlade's constructor)
    GfAssetSetup* m_assetSetup;
};
}  // namespace gf

#endif
