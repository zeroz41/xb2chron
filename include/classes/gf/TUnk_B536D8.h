#ifndef CLASSES_GF_TUNK_B536D8_H
#define CLASSES_GF_TUNK_B536D8_H

#include "classes/ai/State.h"
#include <new>

namespace gf {
// table 0x7100B536D8 (no RTTI): an arena state (getName "StateArenaDestroy"); TUnk_B535D0's setup fn_7100291100 registers it as state 9; its owner is TUnk_B535D0
class TUnk_B536D8 : public ::ai::State {
public:
    // what the arena's Fsm registers: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) TUnk_B536D8(); }
    virtual ~TUnk_B536D8() {}  // slot 0
    virtual const char* getName() const { return "StateArenaDestroy"; }  // slot 2
    virtual void onEnter(void*, ai::State*) {}  // slot 3
    virtual void onLeave(void*, ai::State*) {}  // slot 4
    virtual void onStep(void*, void const*) {}  // slot 5
};
}  // namespace gf

#endif
