#ifndef CLASSES_GF_TUNK_B537B0_H
#define CLASSES_GF_TUNK_B537B0_H

#include "classes/ai/State.h"
#include <new>

namespace gf {
// table 0x7100B537B0 (no RTTI): an arena state (getName "StateArenaResultBattle"); TUnk_B535D0's setup fn_7100291100 registers it as state 6; its owner is TUnk_B535D0
class TUnk_B537B0 : public ::ai::State {
public:
    // what the arena's Fsm registers: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) TUnk_B537B0(); }
    TUnk_B537B0() : m_value(0), m_ptr(nullptr) {}
    virtual ~TUnk_B537B0() {}  // slot 0
    virtual const char* getName() const { return "StateArenaResultBattle"; }  // slot 2
    virtual void onEnter(void* owner, ai::State* prev) { fn_710028F738(owner, prev); }  // slot 3
    virtual void onLeave(void* owner, ai::State* next) { fn_710028F7C4(owner, next); }  // slot 4
    virtual void onStep(void* owner, void const* arg) { fn_710028F830(owner, arg); }  // slot 5

    // Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them. Members: the class's slots tail-call
    // them with their own arguments (this, owner, prev/next/arg); their code is in unit_710028EBB0. What they do:
    // the state's enter/leave/step work (not recovered yet).
    void fn_710028F738(void* owner, ai::State* prev);
    void fn_710028F7C4(void* owner, ai::State* next);
    void fn_710028F830(void* owner, void const* arg);

    // create zeroes both (the names are not the original's); sizeof is 0x38 (registerState)
    int m_value;
    unsigned char pad_1C[4];
    void* m_ptr;
    unsigned char pad_28[0x10];
};
}  // namespace gf

#endif
