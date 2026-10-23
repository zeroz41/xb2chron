#ifndef CLASSES_BTL_CHAINATTACKMANAGER_H
#define CLASSES_BTL_CHAINATTACKMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace btl { class ChainAttackManager; }

namespace btl {
// table 0x7100B3A960
class ChainAttackManager : public ::mm::mtl::PtrSingleton< ::btl::ChainAttackManager> {
public:
    enum TURN_BTN_RESULT_TYPE : int;
    void TurnButtonChllengeResultProc(TURN_BTN_RESULT_TYPE type);
    virtual ~ChainAttackManager();  // slot 0
    static void Create();
    static void Destroy();
};
}  // namespace btl

#endif
