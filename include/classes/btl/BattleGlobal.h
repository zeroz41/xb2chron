#ifndef CLASSES_BTL_BATTLEGLOBAL_H
#define CLASSES_BTL_BATTLEGLOBAL_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace btl { class BattleGlobal; }

namespace btl {
// table 0x7100B3A3E0
class BattleGlobal : public ::mm::mtl::PtrSingleton< ::btl::BattleGlobal> {
public:
    virtual ~BattleGlobal();  // slot 0
};
}  // namespace btl

#endif
