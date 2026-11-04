#ifndef CLASSES_GF_TUNK_B537B0_H
#define CLASSES_GF_TUNK_B537B0_H

#include "classes/ai/State.h"
#include "classes/gf/GfMenuCallContext.h"
#include <new>
namespace gf { class GfGameArena; }
namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B537B0 (no RTTI): an arena state (getName "StateArenaResultBattle"); GfGameArena's setup initialize registers it as state 6; its owner is GfGameArena
class StateArenaResultBattle : public ::ai::State {
public:
    // what the arena's Fsm registers: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) StateArenaResultBattle(); }
    StateArenaResultBattle() : m_timer(0.0f), m_context(nullptr) {}
    virtual ~StateArenaResultBattle() {}  // slot 0
    virtual const char* getName() const { return "StateArenaResultBattle"; }  // slot 2
    virtual void onEnter(void* owner, ai::State* prev) { enter(static_cast<GfGameArena*>(owner), prev); }  // slot 3
    virtual void onLeave(void* owner, ai::State* next) { leave(static_cast<GfGameArena*>(owner), next); }  // slot 4
    virtual void onStep(void* owner, void const* arg) { update(static_cast<GfGameArena*>(owner), *static_cast<fw::UpdateInfo const*>(arg)); }  // slot 5

    // 2.0.0's symbols name them. Members: the class's slots tail-call
    // them with their own arguments (this, owner, prev/next/arg); their code is in unit_710028EBB0. What they do:
    // enter: the arena's +0xC8 helper collects its gimmicks (listUpTBox), m_step = updateStart, a new
    // m_context; leave: drops m_context; update: runs m_step with the step's arguments.
    void enter(GfGameArena* arena, ai::State* prev);
    void leave(GfGameArena* arena, ai::State* next);
    void update(GfGameArena* arena, fw::UpdateInfo const& info);

    // 2.0.0's symbols name them. Members: the steps m_step holds (the
    // class's own code stores them in it and update calls them on this with the step's arguments; the step
    // argument is the frame's fw::UpdateInfo). What they do: the result sequence: updateStart
    // picks updateCamera (the msgObj's m_result is 2 or a TresureNeed is reached) or updateFadeWait; F858 creates
    // and plays the camera cut on the helper's gimmick, m_timer 0.5, then FA80 counts it down to F8D8; F8D8 waits
    // for the fade, calls the helper's playReturnVoice, then F964 (opens GfMenuObjSalvage's openBtlchRecord) or F99C
    // (drops the camera, asks for state 3); F9F0 waits for the menu, FA24 runs the helper's E69C/E878, m_timer
    // 0.5, FAA8 counts it down, FAD0 opens GfMenuObjSalvage::openResult and plays a voice, FB2C waits for the menu
    // and drops the camera, FB70 counts m_timer up to 1 and emits the reward drop
    // (GfArenaReward::dropClearReward), then F99C.
    void updateStart(GfGameArena* arena, fw::UpdateInfo const& info);
    void updateCamera(GfGameArena* arena, fw::UpdateInfo const& info);
    void updateFadeWait(GfGameArena* arena, fw::UpdateInfo const& info);
    void updateResult(GfGameArena* arena, fw::UpdateInfo const& info);
    void updateFinish(GfGameArena* arena, fw::UpdateInfo const& info);
    void updateResultWait(GfGameArena* arena, fw::UpdateInfo const& info);
    void updateTBox(GfGameArena* arena, fw::UpdateInfo const& info);
    void updateCameraWait(GfGameArena* arena, fw::UpdateInfo const& info);
    void updateTBoxWait(GfGameArena* arena, fw::UpdateInfo const& info);
    void updateUI(GfGameArena* arena, fw::UpdateInfo const& info);
    void updateUIWait(GfGameArena* arena, fw::UpdateInfo const& info);
    void updateReturnCamera(GfGameArena* arena, fw::UpdateInfo const& info);

    // the names are not the original's; sizeof is 0x38 (registerState)
    float m_timer;  // create zeroes it; the steps count it down from 0.5 and up to 1
    unsigned char pad_1C[4];
    GfMenuCallContext* m_context;  // create zeroes it; GfMenuCallContext::create's, leave drops it
    void (StateArenaResultBattle::*m_step)(GfGameArena* arena, fw::UpdateInfo const& info);  // the current result step
};
}  // namespace gf

#endif
