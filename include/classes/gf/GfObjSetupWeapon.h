#ifndef CLASSES_GF_GFOBJSETUPWEAPON_H
#define CLASSES_GF_GFOBJSETUPWEAPON_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfObjSetup.h"
#include "classes/gf/GfInitParamWeapon.h"

namespace gf {
// table 0x7100B6A6C8
class GfObjSetupWeapon : public ::gf::GfObjSetup {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfObjSetupWeapon() {}  // slot 1
    GfObjSetupWeapon(const GfInitParamWeapon& param);
    static mm::mtl::RTTI m_rtti;

    // the parameter's pad_94 (createSetupParam copies it)
    int pad_6c;
    unsigned char pad_70;
    // the parameter's append's mount index (createSetupParam copies it; the name is not the original's)
    int m_mountIndex;
    // the parameter append's m_secondList (createSetupParam copies it)
    unsigned char pad_78;
    // a copy of the parameter the weapon was made with (the constructor assigns it; the name is not the original's)
    GfInitParamWeapon m_param;
};
}  // namespace gf

#endif
