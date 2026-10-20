#ifndef CLASSES_GF_GFOBJSETUPBLADE_H
#define CLASSES_GF_GFOBJSETUPBLADE_H

#include "classes/gf/GfObjSetup.h"

namespace gf {
// table 0x7100B6A488
class GfObjSetupBlade : public ::gf::GfObjSetup {
public:
    virtual void getRTTI() const;  // slot 0
    virtual ~GfObjSetupBlade();  // slot 1
};
}  // namespace gf

#endif
