#ifndef CLASSES_GF_GFALLOCATORMANAGER_H
#define CLASSES_GF_GFALLOCATORMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfAllocatorManager; }

namespace gf {
// table 0x7100B597F0
class GfAllocatorManager : public ::mm::mtl::PtrSingleton< ::gf::GfAllocatorManager> {
public:
    virtual ~GfAllocatorManager();  // slot 0
};
}  // namespace gf

#endif
