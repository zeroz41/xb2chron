#ifndef CLASSES_GF_GFOBJSETUPENWEAPON_H
#define CLASSES_GF_GFOBJSETUPENWEAPON_H

#include "classes/gf/GfObjSetup.h"

namespace gf {
// table 0x7100B6A708
class GfObjSetupEnWeapon : public ::gf::GfObjSetup {
public:
    virtual void getRTTI() const;  // slot 0
    virtual ~GfObjSetupEnWeapon();  // slot 1
};
}  // namespace gf

#endif
