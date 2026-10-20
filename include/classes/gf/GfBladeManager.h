#ifndef CLASSES_GF_GFBLADEMANAGER_H
#define CLASSES_GF_GFBLADEMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfBladeManager; }

namespace gf {
// table 0x7100B53A90
class GfBladeManager : public ::mm::mtl::PtrSingleton< ::gf::GfBladeManager> {
public:
    virtual ~GfBladeManager();  // slot 0
};
}  // namespace gf

#endif
