#ifndef CLASSES_BTL_SPATTACKMANAGER_H
#define CLASSES_BTL_SPATTACKMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace btl { class SpAttackManager; }

namespace btl {
// table 0x7100B3BDA8
class SpAttackManager : public ::mm::mtl::PtrSingleton< ::btl::SpAttackManager> {
public:
    virtual ~SpAttackManager();  // slot 0
    static void Create();
    static void Destroy();
};
}  // namespace btl

#endif
