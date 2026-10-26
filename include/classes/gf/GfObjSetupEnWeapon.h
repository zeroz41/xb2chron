#ifndef CLASSES_GF_GFOBJSETUPENWEAPON_H
#define CLASSES_GF_GFOBJSETUPENWEAPON_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfObjSetup.h"
#include "classes/gf/GfInitParamEnWeapon.h"

namespace gf {
// table 0x7100B6A708
class GfObjSetupEnWeapon : public ::gf::GfObjSetup {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfObjSetupEnWeapon() {}  // slot 1
    static mm::mtl::RTTI m_rtti;
    GfObjSetupEnWeapon(const GfInitParamEnWeapon& param);
    // the mount index of the model: createSetupParam copies the param's append's getMountIndex() (the name is not
    // the original's)
    unsigned int m_mountIndex;
};
}  // namespace gf

#endif
