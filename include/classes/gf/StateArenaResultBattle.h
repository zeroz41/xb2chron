#ifndef CLASSES_GF_TUNK_B537B0_H
#define CLASSES_GF_TUNK_B537B0_H

#include "classes/ai/State.h"
#include "classes/gf/GfMenuCallContext.h"
#include <new>

namespace gf {
// table 0x7100B537B0 (no RTTI): an arena state (getName "StateArenaResultBattle"); GfGameArena's setup initialize registers it as state 6; its owner is GfGameArena
class StateArenaResultBattle : public ::ai::State {
public:
    // what the arena's Fsm registers: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) StateArenaResultBattle(); }
    StateArenaResultBattle() : m_timer(0.0f), m_context(nullptr) {}
    virtual ~StateArenaResultBattle() {}  // slot 0
    virtual const char* getName() const { return "StateArenaResultBattle"; }  // slot 2
    virtual void onEnter(void* owner, ai::State* prev) { fn_710028F738(owner, prev); }  // slot 3
    virtual void onLeave(void* owner, ai::State* next) { fn_710028F7C4(owner, next); }  // slot 4
    virtual void onStep(void* owner, void const* arg) { fn_710028F830(owner, arg); }  // slot 5

    // Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them. Members: the class's slots tail-call
    // them with their own arguments (this, owner, prev/next/arg); their code is in unit_710028EBB0. What they do:
    // fn_710028F738: the arena's +0xC8 helper collects its gimmicks (listUpTBox), m_step = fn_710028F770, a new
    // m_context; fn_710028F7C4: drops m_context; fn_710028F830: runs m_step with the step's arguments.
    void fn_710028F738(void* owner, ai::State* prev);
    void fn_710028F7C4(void* owner, ai::State* next);
    void fn_710028F830(void* owner, void const* arg);

    // Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them. Members: the steps m_step holds (the
    // class's own code stores them in it and fn_710028F830 calls them on this with the step's arguments; the step
    // argument is a float pair, [0] and [1] the two frame times). What they do: the result sequence: fn_710028F770
    // picks fn_710028F858 (the msgObj's m_result is 2 or a TresureNeed is reached) or fn_710028F8D8; F858 creates
    // and plays the camera cut on the helper's gimmick, m_timer 0.5, then FA80 counts it down to F8D8; F8D8 waits
    // for the fade, calls the helper's playReturnVoice, then F964 (opens GfMenuObjSalvage's openBtlchRecord) or F99C
    // (drops the camera, asks for state 3); F9F0 waits for the menu, FA24 runs the helper's E69C/E878, m_timer
    // 0.5, FAA8 counts it down, FAD0 opens GfMenuObjSalvage::openResult and plays a voice, FB2C waits for the menu
    // and drops the camera, FB70 counts m_timer up to 1 and emits the reward drop (fn_710028F0A4), then F99C.
    void fn_710028F770(void* owner, void const* arg);
    void fn_710028F858(void* owner, void const* arg);
    void fn_710028F8D8(void* owner, void const* arg);
    void fn_710028F964(void* owner, void const* arg);
    void fn_710028F99C(void* owner, void const* arg);
    void fn_710028F9F0(void* owner, void const* arg);
    void fn_710028FA24(void* owner, void const* arg);
    void fn_710028FA80(void* owner, void const* arg);
    void fn_710028FAA8(void* owner, void const* arg);
    void fn_710028FAD0(void* owner, void const* arg);
    void fn_710028FB2C(void* owner, void const* arg);
    void fn_710028FB70(void* owner, void const* arg);

    // the names are not the original's; sizeof is 0x38 (registerState)
    float m_timer;  // create zeroes it; the steps count it down from 0.5 and up to 1
    unsigned char pad_1C[4];
    GfMenuCallContext* m_context;  // create zeroes it; GfMenuCallContext::create's, fn_710028F7C4 drops it
    void (StateArenaResultBattle::*m_step)(void* owner, void const* arg);  // the current result step
};
}  // namespace gf

#endif
