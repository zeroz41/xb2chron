#ifndef CLASSES_GF_TUNK_B535D0_H
#define CLASSES_GF_TUNK_B535D0_H

#include "classes/fw/MessageObject.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace gf {
// table 0x7100B535D0 (the fw::MessageObject base's at +0x38, offset 8); the base at 0 is
// mm::mtl::PtrSingleton<TUnk_B535D0> (its table 0x7100B53628). No RTTI or 1.0.0 symbol names it: the arena manager
// of gf_game_arena's unit (its constructor fn_7100290FA0 installs both tables; the arena play commands send it
// MsgUnk_1000034). Only what gf_play_command uses is declared so far (size 0x18E0, layout not recovered).
class TUnk_B535D0 : public ::mm::mtl::PtrSingleton<TUnk_B535D0>, public ::fw::MessageObject {
public:
    // Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them. Members: their code is in
    // gf_game_arena's unit and the play commands call them on PtrSingleton<TUnk_B535D0>'s instance. What they do:
    // read the state object the pointer at +0x30 holds and answer whether its word at +8 is 9
    // (GfPlayComMapjumpForLeaveArena::update waits for it), 3 (GfPlayComWaitArenaStateField::update; also
    // fn_710028C9CC) or 8 (GfPlayComStartChallengeBattle::update).
    bool fn_7100291CAC();
    bool fn_7100291DA0();
    bool fn_7100291E00();
};
}  // namespace gf

#endif
