#ifndef CLASSES_GF_GFGAMEINSIDEBATTLELOCK_H
#define CLASSES_GF_GFGAMEINSIDEBATTLELOCK_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfGameInsideBattleLock; }

namespace gf {
// table 0x7100B548F8
class GfGameInsideBattleLock : public ::mm::mtl::PtrSingleton< ::gf::GfGameInsideBattleLock> {
public:
    virtual ~GfGameInsideBattleLock();  // slot 0
};
}  // namespace gf

#endif
