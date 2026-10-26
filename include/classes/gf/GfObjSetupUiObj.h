#ifndef CLASSES_GF_GFOBJSETUPUIOBJ_H
#define CLASSES_GF_GFOBJSETUPUIOBJ_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfObjSetup.h"
#include "classes/gf/GfInitParamUiObj.h"
#include "mm/mtl/FixStr.h"

namespace gf {
// table 0x7100B6A808
class GfObjSetupUiObj : public ::gf::GfObjSetup {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfObjSetupUiObj() {}  // slot 1
    static mm::mtl::RTTI m_rtti;
    GfObjSetupUiObj(const GfInitParamUiObj& param);
    // the asset setup's archive file without folder and extension (createSetupParam; the name is not the
    // original's)
    mm::mtl::FixStr<128> m_arcName;
    // "S_idle" (the constructor and createSetupParam set it; the name is not the original's)
    mm::mtl::FixStr<32> m_stateName;
};
}  // namespace gf

#endif
