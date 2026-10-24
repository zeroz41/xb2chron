#ifndef CLASSES_GF_GFOBJSETUPMAP_H
#define CLASSES_GF_GFOBJSETUPMAP_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfObjSetup.h"

namespace gf {
// table 0x7100B6A548
class GfObjSetupMap : public ::gf::GfObjSetup {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfObjSetupMap() {}  // slot 1
    static mm::mtl::RTTI m_rtti;
    GfObjSetupMap(const GfInitParam& param);

    // createSetupParam(MapSeamless) stores the parameter's object id in pad_70 when its pad_90 is set, here
    // otherwise
    unsigned int pad_6c;
    unsigned int pad_70;
    // set by createSetupParam(MapSeamless) when the parameter's pad_98 is not null
    bool pad_74;
    // set by createSetupParam(MapSeamless)
    bool pad_75;
};
}  // namespace gf

#endif
