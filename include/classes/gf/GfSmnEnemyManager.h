#ifndef CLASSES_GF_GFSMNENEMYMANAGER_H
#define CLASSES_GF_GFSMNENEMYMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfSmnEnemyManager; }

namespace gf {
// table 0x7100B59168
class GfSmnEnemyManager : public ::mm::mtl::PtrSingleton< ::gf::GfSmnEnemyManager> {
public:
    virtual ~GfSmnEnemyManager();  // slot 0
};
}  // namespace gf

#endif
