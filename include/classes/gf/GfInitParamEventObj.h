#ifndef CLASSES_GF_GFINITPARAMEVENTOBJ_H
#define CLASSES_GF_GFINITPARAMEVENTOBJ_H

#include "classes/gf/GfInitParam.h"

namespace gf {
// table 0x7100B3FAF8
class GfInitParamEventObj : public ::gf::GfInitParam {
public:
    // inline: no copy of it exists (event::ModelObj::setupModel builds one on the stack)
    GfInitParamEventObj() : GfInitParam(11, 7) { m_assetSetup = nullptr; }
};
}  // namespace gf

#endif
