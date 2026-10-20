#ifndef CLASSES_GF_GFOBJSETUPWEAPON_H
#define CLASSES_GF_GFOBJSETUPWEAPON_H

#include "classes/gf/GfObjSetup.h"

namespace gf {
// table 0x7100B6A6C8
class GfObjSetupWeapon : public ::gf::GfObjSetup {
public:
    virtual void getRTTI() const;  // slot 0
    virtual ~GfObjSetupWeapon();  // slot 1
};
}  // namespace gf

#endif
