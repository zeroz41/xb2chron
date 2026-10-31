#ifndef GF_PC_STATEUTILBATTLE_H
#define GF_PC_STATEUTILBATTLE_H

#include "classes/btl/BattleCharacter.h"
#include "classes/gf/pc/StateBattleBase.h"

namespace gf { namespace pc {
// the PC's battle state helpers
class StateUtilBattle {
public:
    // whether state is one of the battle states
    static bool IsBattleState(STATE_ID state);
    // the battle state that runs the battle character's action
    static STATE_ID ConversionActionToState(btl::BattleCharacter::ACTION_ID action);
    // the battle character's action a battle state runs
    static btl::BattleCharacter::ACTION_ID ConversionStateToAction(STATE_ID state);
};
}}  // namespace gf::pc

#endif
