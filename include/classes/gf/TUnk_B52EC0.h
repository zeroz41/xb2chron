#ifndef CLASSES_GF_TUNK_B52EC0_H
#define CLASSES_GF_TUNK_B52EC0_H

#include "classes/ai/State.h"
#include "classes/gf/IGfEvent.h"
#include <new>
#include "classes/gf/GfEvent.h"
#include "classes/gf/TUnk_B535D0.h"
#include "classes/gf/TUnk_28D7B8.h"

namespace gf { class MapjumpCallbackInfo; enum GEV : int; }

namespace gf {
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (code in sequential_play's unit_71003214F4, which
// has no source yet). A free function: callers pass only a bool. What it does: unless the bool is set, answers false
// when GfGameManager::isLeaveGameForDebug, else needs isEnableOpenMainMenu and fn_71002AC580; then builds a map-jump
// request on the stack. TUnk_B52EC0's onStep calls it with true and moves to state 2 when it answers true.
bool fn_71003214F4(bool force);

// table 0x7100B52EC0 (no RTTI): an arena state (getName "StateArenaField"; TUnk_B535D0's setup fn_7100291100 registers it
// as state 3, sizeof 0x20); its owner is TUnk_B535D0. Its slots and its key function gevMapjump (0x710028F4B8)
// are in unit_710028EBB0, which defines them (inline slots in the class, gevMapjump in the .cpp is the key function).
class TUnk_B52EC0 : public ::ai::State, public ::gf::IGfEvent {
public:
    // what the arena's Fsm registers: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) TUnk_B52EC0(); }
    virtual ~TUnk_B52EC0() {}  // slot 0
    virtual const char* getName() const { return "StateArenaField"; }  // slot 2
    virtual void onEnter(void* owner, ai::State*) {  // slot 3
        TUnk_B535D0* arena = static_cast<TUnk_B535D0*>(owner);
        GfEvent::addEventCallback(this);
        arena->m_partySetup->fn_710028DA24();
        arena->fn_7100291CF4()->fn_7100290598(arena->m_ids);
    }
    virtual void onLeave(void*, ai::State*) { GfEvent::removeEventCallback(this); }  // slot 4
    virtual void onStep(void* owner, void const*) {  // slot 5
        TUnk_B535D0* arena = static_cast<TUnk_B535D0*>(owner);
        if (arena->fn_7100291D68()) {
            if (GfGameManager::isMapjump()) {
                requestState(0);
            } else if (fn_71003214F4(true)) {
                requestState(2);
            }
        }
    }
    // the key function (defined in the .cpp)
    virtual void gevMapjump(gf::GEV, gf::MapjumpCallbackInfo const&);  // slot 7
};
}  // namespace gf

#endif
