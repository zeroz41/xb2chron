#ifndef CLASSES_GF_GFOBJSETUPFIELDOBJ_H
#define CLASSES_GF_GFOBJSETUPFIELDOBJ_H

#include "classes/gf/GfObjSetup.h"

namespace gf {
// table 0x7100B6A688
class GfObjSetupFieldObj : public ::gf::GfObjSetup {
public:
    virtual void getRTTI() const;  // slot 0
    virtual ~GfObjSetupFieldObj();  // slot 1
};
}  // namespace gf

#endif
