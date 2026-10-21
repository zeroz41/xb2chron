#ifndef CLASSES_GF_GFITEMMANAGER_H
#define CLASSES_GF_GFITEMMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfItemManager; }

namespace gf {
// table 0x7100B56C48
class GfItemManager : public ::mm::mtl::PtrSingleton< ::gf::GfItemManager> {
public:
    virtual ~GfItemManager();  // slot 0
};
}  // namespace gf

#endif
