#ifndef CLASSES_GF_TUNK_B52EC0_H
#define CLASSES_GF_TUNK_B52EC0_H

#include "classes/ai/State.h"
#include "classes/gf/IGfEvent.h"
#include <new>
#include "classes/gf/GfEvent.h"
#include "classes/gf/GfGameArena.h"
#include "classes/gf/GfArenaParty.h"

namespace gf { class MapjumpCallbackInfo; enum GEV : int; }

namespace gf {
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (code in sequential_play's unit_71003214F4, which
// has no source yet). A free function: callers pass only a bool. What it does: unless the bool is set, answers false
// when GfGameManager::isLeaveGameForDebug, else needs isEnableOpenMainMenu and isBattleArenaActive; then builds a map-jump
// request on the stack. StateArenaField's onStep calls it with true and moves to state 2 when it answers true.
bool fn_71003214F4(bool force);

// table 0x7100B52EC0 (no RTTI): an arena state (getName "StateArenaField"; GfGameArena's setup initialize registers it
// as state 3, sizeof 0x20); its owner is GfGameArena. Its slots and its key function gevMapjump (0x710028F4B8)
// are in unit_710028EBB0, which defines them (inline slots in the class, gevMapjump in the .cpp is the key function).
class StateArenaField : public ::ai::State, public ::gf::IGfEvent {
public:
    // what the arena's Fsm registers: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) StateArenaField(); }
    virtual ~StateArenaField() {}  // slot 0
    virtual const char* getName() const { return "StateArenaField"; }  // slot 2
    virtual void onEnter(void* owner, ai::State*) {  // slot 3
        GfGameArena* arena = static_cast<GfGameArena*>(owner);
        GfEvent::addEventCallback(this);
        arena->m_partySetup->addFieldBlade();
        arena->fn_7100291CF4()->fn_7100290598(arena->m_ids);
    }
    virtual void onLeave(void*, ai::State*) { GfEvent::removeEventCallback(this); }  // slot 4
    virtual void onStep(void* owner, void const*) {  // slot 5
        GfGameArena* arena = static_cast<GfGameArena*>(owner);
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
