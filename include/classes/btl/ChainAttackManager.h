#ifndef CLASSES_BTL_CHAINATTACKMANAGER_H
#define CLASSES_BTL_CHAINATTACKMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace btl { class ChainAttackManager; }

namespace btl {
// table 0x7100B3A960
class ChainAttackManager : public ::mm::mtl::PtrSingleton< ::btl::ChainAttackManager> {
public:
    virtual ~ChainAttackManager();  // slot 0
};
}  // namespace btl

#endif
