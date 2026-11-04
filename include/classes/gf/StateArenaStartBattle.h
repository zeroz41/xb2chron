#ifndef CLASSES_GF_TUNK_B53720_H
#define CLASSES_GF_TUNK_B53720_H

#include "classes/ai/State.h"
#include <new>
namespace gf { class GfGameArena; }
namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B53720 (no RTTI): an arena state (getName "StateArenaStartBattle"); GfGameArena's setup initialize registers it as state 4; its owner is GfGameArena
class StateArenaStartBattle : public ::ai::State {
public:
    // what the arena's Fsm registers: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) StateArenaStartBattle(); }
    virtual ~StateArenaStartBattle() {}  // slot 0
    virtual const char* getName() const { return "StateArenaStartBattle"; }  // slot 2
    virtual void onEnter(void* owner, ai::State* prev) { enter(static_cast<GfGameArena*>(owner), prev); }  // slot 3
    virtual void onLeave(void* owner, ai::State* next) { leave(static_cast<GfGameArena*>(owner), next); }  // slot 4
    virtual void onStep(void* owner, void const* arg) { update(static_cast<GfGameArena*>(owner), *static_cast<fw::UpdateInfo const*>(arg)); }  // slot 5

    // 2.0.0's symbols name them. Members: the class's slots tail-call
    // them with their own arguments (this, owner, prev/next/arg); their code is in unit_710028EBB0. What they do:
    // the state's enter/leave/step work (not recovered yet).
    void enter(GfGameArena* arena, ai::State* prev);
    void leave(GfGameArena* arena, ai::State* next);
    void update(GfGameArena* arena, fw::UpdateInfo const& info);
};
}  // namespace gf

#endif
