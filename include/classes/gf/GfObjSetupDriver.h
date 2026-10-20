#ifndef CLASSES_GF_GFOBJSETUPDRIVER_H
#define CLASSES_GF_GFOBJSETUPDRIVER_H

#include "classes/gf/GfObjSetup.h"

namespace gf {
// table 0x7100B6A508
class GfObjSetupDriver : public ::gf::GfObjSetup {
public:
    virtual void getRTTI() const;  // slot 0
    virtual ~GfObjSetupDriver();  // slot 1
};
}  // namespace gf

#endif
