#ifndef CLASSES_GF_GFINITPARAMBELONGING_H
#define CLASSES_GF_GFINITPARAMBELONGING_H

#include "classes/gf/GfInitParam.h"
#include "gf/GfAppend.h"

namespace gf { class GfInitParamDriver; }

namespace gf {
// table 0x7100B69F30
class GfInitParamBelonging : public ::gf::GfInitParam {
public:
    // a setup to use instead of the factory's own (the name is not the original's). A member of each kind,
    // not of GfInitParam: the copy assignments copy it with the kind's own fields, apart from the base's
    // (GfInitParamDriver::operator=, GfObjSetupBlade's constructor)
    GfAssetSetup* m_assetSetup;

    // inline: no copy of it exists (fn_7100528684 builds one on the stack; m_assetSetup is cleared before
    // m_append's constructor runs, m_belongingValues is left as it is)
    GfInitParamBelonging()
        : GfInitParam(13, 6), m_assetSetup(nullptr), m_append(), m_isForDriver(false), m_driverParam(nullptr),
          pad_130(true) {}

    // the model: createSetupParam takes its getMountIndex()
    GfAppend m_append;
    // the four values GfObjFactory::createBelonging hands GfAppendUtil::setupBelonging without m_isForDriver (the
    // names are not the original's)
    unsigned short m_belongingValues[4];
    // whether GfObjFactory::createBelonging sets the belonging up for m_driverParam's driver (the name is not the
    // original's)
    bool m_isForDriver;
    unsigned char pad_121[0x128 - 0x121];
    const GfInitParamDriver* m_driverParam;  // GfAppendUtil::setupBelongingForDriver's (the name is not the original's)
    // whether the setup's pad_50 is 1.0f (else 0.0f; createSetupParam)
    bool pad_130;
};
}  // namespace gf

#endif
