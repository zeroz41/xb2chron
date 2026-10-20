#ifndef CLASSES_GF_GFEVTMODELNPC_H
#define CLASSES_GF_GFEVTMODELNPC_H

#include "classes/gf/GfEvtModel.h"

namespace gf {
// table 0x7100B53E68
class GfEvtModelNpc : public ::gf::GfEvtModel {
public:
    virtual ~GfEvtModelNpc();  // slot 0
    virtual void getRTTI() const;  // slot 2
};
}  // namespace gf

#endif
