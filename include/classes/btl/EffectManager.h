#ifndef CLASSES_BTL_EFFECTMANAGER_H
#define CLASSES_BTL_EFFECTMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace btl { class EffectManager; }

namespace btl {
// table 0x7100B3BB38
class EffectManager : public ::mm::mtl::PtrSingleton< ::btl::EffectManager> {
public:
    virtual ~EffectManager();  // slot 0
    // Create: 1.0.0's name (fn_710009733C in 3.0.1): 1.0.0's BattleManager::Initialize calls it after
    // HateRingManager::Create, as 3.0.1's does
    static void Create();
    static void Destroy();
};
}  // namespace btl

#endif
