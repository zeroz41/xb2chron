#ifndef CLASSES_GF_GFOBJSETUPEXTRA_H
#define CLASSES_GF_GFOBJSETUPEXTRA_H

#include "classes/gf/GfObjSetup.h"

namespace gf {
// table 0x7100B6A788
class GfObjSetupExtra : public ::gf::GfObjSetup {
public:
    virtual void getRTTI() const;  // slot 0
    virtual ~GfObjSetupExtra();  // slot 1
};
}  // namespace gf

#endif
