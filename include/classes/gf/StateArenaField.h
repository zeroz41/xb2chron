#ifndef CLASSES_GF_TUNK_B52EC0_H
#define CLASSES_GF_TUNK_B52EC0_H

#include "classes/ai/State.h"
#include "classes/gf/IGfEvent.h"
#include <new>
#include "classes/gf/GfEvent.h"
#include "classes/gf/GfGameArena.h"
#include "classes/gf/GfArenaParty.h"
#include "gf/GfPlayFactory.h"

namespace gf { class MapjumpCallbackInfo; enum GEV : int; }

namespace gf {
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
        GfArenaUtil::applyChallengeStatus(*arena->getSaveInfo(), arena->m_ids);
    }
    virtual void onLeave(void*, ai::State*) { GfEvent::removeEventCallback(this); }  // slot 4
    virtual void onStep(void* owner, void const*) {  // slot 5
        GfGameArena* arena = static_cast<GfGameArena*>(owner);
        if (arena->isDestroyNow()) {
            if (GfGameManager::isMapjump()) {
                requestState(0);
            } else if (GfPlayFactory::createLeaveBattleArena(true)) {
                requestState(2);
            }
        }
    }
    // the key function (defined in the .cpp)
    virtual void gevMapjump(gf::GEV, gf::MapjumpCallbackInfo const&);  // slot 7
};
}  // namespace gf

#endif
