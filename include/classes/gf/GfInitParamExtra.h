#ifndef CLASSES_GF_GFINITPARAMEXTRA_H
#define CLASSES_GF_GFINITPARAMEXTRA_H

#include "classes/gf/GfInitParam.h"
#include "gf/GfAppend.h"

namespace gf {
// table 0x7100B69F08
class GfInitParamExtra : public ::gf::GfInitParam {
public:
    // the model: createSetupParam takes its getMountIndex()
    GfAppend m_append;
};
}  // namespace gf

#endif
