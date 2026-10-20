#ifndef CLASSES_GF_GFOBJSETUPUIOBJ_H
#define CLASSES_GF_GFOBJSETUPUIOBJ_H

#include "classes/gf/GfObjSetup.h"

namespace gf {
// table 0x7100B6A808
class GfObjSetupUiObj : public ::gf::GfObjSetup {
public:
    virtual void getRTTI() const;  // slot 0
    virtual ~GfObjSetupUiObj();  // slot 1
};
}  // namespace gf

#endif
