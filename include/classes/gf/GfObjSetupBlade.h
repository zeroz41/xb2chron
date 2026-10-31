#ifndef CLASSES_GF_GFOBJSETUPBLADE_H
#define CLASSES_GF_GFOBJSETUPBLADE_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfObjSetup.h"
#include "classes/gf/GfInitParamBlade.h"
#include "gf/GfGameUtil.h"

namespace gf {
// table 0x7100B6A488
class GfObjSetupBlade : public ::gf::GfObjSetup {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfObjSetupBlade() {}  // slot 1
    // out of line: the symbols name its C1 (the alias of the C2 an out-of-line constructor emits), which sits
    // among gf_obj_setup.cpp's own definitions in both builds
    GfObjSetupBlade(const GfInitParamBlade& param);
    static mm::mtl::RTTI m_rtti;

    // the parameter's pad_98 (createSetupParam copies it)
    int pad_6c;
    unsigned char pad_70;
    // GfGameUtil::isCondBladeModel of the blade (the constructor sets it; the name is not the original's)
    bool m_isCondBladeModel;
    int pad_74;
    // a copy of the parameter the blade was made with (the constructor assigns it; the name is not the original's)
    GfInitParamBlade m_param;
};
}  // namespace gf

#endif
