#ifndef CLASSES_GF_GFGAMEDEPOPMETERMANAGER_H
#define CLASSES_GF_GFGAMEDEPOPMETERMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfGameDepopMeterManager; }

namespace gf {
// table 0x7100B56680
class GfGameDepopMeterManager : public ::mm::mtl::PtrSingleton< ::gf::GfGameDepopMeterManager> {
public:
    virtual ~GfGameDepopMeterManager();  // slot 0
};
}  // namespace gf

#endif
