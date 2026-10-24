#ifndef CLASSES_GF_GFOBJSETUPGIMMICK_H
#define CLASSES_GF_GFOBJSETUPGIMMICK_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfObjSetup.h"
#include "mm/mtl/FixStr.h"
#include "classes/gf/GfInitParamGimmick.h"
#include "classes/gf/DataParamAcc.h"

namespace gf {
// table 0x7100B6A648
class GfObjSetupGimmick : public ::gf::GfObjSetup {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfObjSetupGimmick() {}  // slot 1
    static mm::mtl::RTTI m_rtti;

    GfObjSetupGimmick(const GfInitParamGimmick& param);

    unsigned int pad_6c;
    // the state the object starts in: "S_idle" (the name is not the original's)
    mm::mtl::FixStr<32> m_stateName;
    // the parameter's pad_90 (createSetupParam copies it)
    void* pad_98;
    bool pad_a0;
    bool pad_a1;
};
}  // namespace gf

#endif
