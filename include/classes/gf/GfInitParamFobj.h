#ifndef CLASSES_GF_GFINITPARAMFOBJ_H
#define CLASSES_GF_GFINITPARAMFOBJ_H

#include "classes/gf/GfInitParam.h"

namespace gf {
// table 0x7100B52930
class GfInitParamFobj : public ::gf::GfInitParam {
public:
    // inline: no copy of it exists. GfFobjDropitem's emitDropgold and fn_7100287E30 build one on the stack with these
    // values
    GfInitParamFobj() : GfInitParam(9) {
        m_assetSetup = nullptr;
        pad_94 = 0;
        m_isDropItem = false;
        pad_81 = false;
    }

    // the constructor leaves it; GfFobjDropitem's emitDropgold and fn_7100287E30 and GmkPrecious::createGobInst
    // set 2 (the store order of their code puts it after the constructor's)
    int pad_90;
    // createSetupParam formats "paramid%d" with it
    unsigned char pad_94;
    // GfObjFactory::createFieldObj registers a GfFobjDropitem for the object when set (the name is not the original's)
    bool m_isDropItem;
};
}  // namespace gf

#endif
