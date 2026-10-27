#ifndef CLASSES_GF_TUNK_B53690_H
#define CLASSES_GF_TUNK_B53690_H

#include "classes/ai/State.h"
#include <new>

namespace gf {
// table 0x7100B53690 (no RTTI): an arena state (getName "StateArenaLeave"); TUnk_B535D0's setup fn_7100291100 registers it as state 2; its owner is TUnk_B535D0
class TUnk_B53690 : public ::ai::State {
public:
    // what the arena's Fsm registers: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) TUnk_B53690(); }
    virtual ~TUnk_B53690() {}  // slot 0
    virtual const char* getName() const { return "StateArenaLeave"; }  // slot 2
    virtual void onEnter(void* owner, ai::State* prev) { fn_710028F444(owner, prev); }  // slot 3
    virtual void onLeave(void* owner, ai::State* next) { fn_710028F46C(owner, next); }  // slot 4
    virtual void onStep(void* owner, void const* arg) { fn_710028F470(owner, arg); }  // slot 5

    // Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them. Members: the class's slots tail-call
    // them with their own arguments (this, owner, prev/next/arg); their code is in unit_710028EBB0. What they do:
    // the state's enter/leave/step work (not recovered yet).
    void fn_710028F444(void* owner, ai::State* prev);
    void fn_710028F46C(void* owner, ai::State* next);
    void fn_710028F470(void* owner, void const* arg);
};
}  // namespace gf

#endif
