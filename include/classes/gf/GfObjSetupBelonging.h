#ifndef CLASSES_GF_GFOBJSETUPBELONGING_H
#define CLASSES_GF_GFOBJSETUPBELONGING_H

#include "classes/gf/GfObjSetup.h"

namespace gf {
// table 0x7100B6A748
class GfObjSetupBelonging : public ::gf::GfObjSetup {
public:
    virtual void getRTTI() const;  // slot 0
    virtual ~GfObjSetupBelonging();  // slot 1
};
}  // namespace gf

#endif
