#ifndef CLASSES_GF_GFMEMMANAGER_H
#define CLASSES_GF_GFMEMMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfMemManager; }

namespace gf {
// table 0x7100B59868
class GfMemManager : public ::mm::mtl::PtrSingleton< ::gf::GfMemManager> {
public:
    virtual ~GfMemManager();  // slot 0
};
}  // namespace gf

#endif
