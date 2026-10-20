#ifndef CLASSES_GF_GFEVTMODELSALVAGE_H
#define CLASSES_GF_GFEVTMODELSALVAGE_H

#include "classes/gf/GfEvtModelDriver.h"

namespace gf {
// table 0x7100B53D28
class GfEvtModelSalvage : public ::gf::GfEvtModelDriver {
public:
    virtual ~GfEvtModelSalvage();  // slot 0
    virtual void getRTTI() const;  // slot 2
};
}  // namespace gf

#endif
