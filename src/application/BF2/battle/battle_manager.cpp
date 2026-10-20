#include "classes/btl/BattleManager.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace btl {

bool BattleManager::isInitialized() {
    BattleManager* manager = mm::mtl::PtrSingleton<BattleManager>::sys();
    if (manager != nullptr) {
        return manager->m_initialized;
    }
    return false;
}

}  // namespace btl
