#ifndef CLASSES_GF_GFINITPARAMFOBJ_H
#define CLASSES_GF_GFINITPARAMFOBJ_H

#include "classes/gf/GfInitParam.h"

namespace gf {
// table 0x7100B52930
class GfInitParamFobj : public ::gf::GfInitParam {
public:
    // a setup to use instead of the factory's own (the name is not the original's). A member of each kind,
    // not of GfInitParam: the copy assignments copy it with the kind's own fields, apart from the base's
    // (GfInitParamDriver::operator=, GfObjSetupBlade's constructor)
    GfAssetSetup* m_assetSetup;
    // inline: no copy of it exists. GfFobjDropitem's emitDropgold and emitDropEtherCube build one on the stack with these
    // values
    GfInitParamFobj() : GfInitParam(9) {
        m_assetSetup = nullptr;
        pad_94 = 0;
        m_isDropItem = false;
        pad_81 = false;
    }

    // the constructor leaves it; GfFobjDropitem's emitDropgold and emitDropEtherCube and GmkPrecious::createGobInst
    // set 2 (the store order of their code puts it after the constructor's)
    int pad_90;
    // createSetupParam formats "paramid%d" with it
    unsigned char pad_94;
    // GfObjFactory::createFieldObj registers a GfFobjDropitem for the object when set (the name is not the original's)
    bool m_isDropItem;
};
}  // namespace gf

#endif
