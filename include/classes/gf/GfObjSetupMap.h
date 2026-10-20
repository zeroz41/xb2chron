#ifndef CLASSES_GF_GFOBJSETUPMAP_H
#define CLASSES_GF_GFOBJSETUPMAP_H

#include "classes/gf/GfObjSetup.h"

namespace gf {
// table 0x7100B6A548
class GfObjSetupMap : public ::gf::GfObjSetup {
public:
    virtual void getRTTI() const;  // slot 0
    virtual ~GfObjSetupMap();  // slot 1
};
}  // namespace gf

#endif
