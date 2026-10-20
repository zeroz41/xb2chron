#ifndef CLASSES_GF_GFOBJSETUPMOB_H
#define CLASSES_GF_GFOBJSETUPMOB_H

#include "classes/gf/GfObjSetup.h"

namespace gf {
// table 0x7100B6A608
class GfObjSetupMob : public ::gf::GfObjSetup {
public:
    virtual void getRTTI() const;  // slot 0
    virtual ~GfObjSetupMob();  // slot 1
};
}  // namespace gf

#endif
