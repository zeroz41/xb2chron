#ifndef CLASSES_GF_GFOBJSETUPNPC_H
#define CLASSES_GF_GFOBJSETUPNPC_H

#include "classes/gf/GfObjSetup.h"

namespace gf {
// table 0x7100B6A5C8
class GfObjSetupNpc : public ::gf::GfObjSetup {
public:
    virtual void getRTTI() const;  // slot 0
    virtual ~GfObjSetupNpc();  // slot 1
};
}  // namespace gf

#endif
