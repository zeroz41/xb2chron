#ifndef CLASSES_GF_TUNK_B53118_H
#define CLASSES_GF_TUNK_B53118_H

#include "classes/ai/State.h"
#include <new>
#include "classes/gf/IGfEvent.h"
#include "classes/gf/GfEvent.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/GfArenaBattle.h"
#include "classes/gf/GfGameArena.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/SCOM_ACHIEV_INC.h"
#include "btl/Utility.h"

namespace gf { class MapjumpCallbackInfo; enum GEV : int; }

namespace gf {

// table 0x7100B53118 (no RTTI): an arena state (getName "StateArenaReturnBattle"; GfGameArena's setup registers
// it); its owner is GfGameArena
class StateArenaReturnBattle : public ::ai::State, public ::gf::IGfEvent {
public:
    // what the arena's Fsm registers: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) StateArenaReturnBattle(); }
    virtual ~StateArenaReturnBattle() {}  // slot 0
    virtual const char* getName() const { return "StateArenaReturnBattle"; }  // slot 2
    virtual void onEnter(void*, ai::State*) { GfEvent::addEventCallback(this); }  // slot 3
    virtual void onLeave(void*, ai::State*) {  // slot 4
        GfEvent::removeEventCallback(this);
        btl::Utility::EndChallengeBattleCallback();
    }
    virtual void onStep(void* owner, void const*) {  // slot 5
        GfGameArena* arena = static_cast<GfGameArena*>(owner);
        SCOM_ACHIEV_INC::createCbCube(GfGameManager::getBattleArenaEtherCube());
        arena->m_msgObj->mapjumpForReturnField();
        GfMenuManager::unloadBchUI();
        if (arena->m_msgObj->m_result == 5) {
            requestState(3);
        } else {
            requestState(6);
        }
    }
    // the key function (defined in the .cpp)
    virtual void gevMapjump(gf::GEV gev, gf::MapjumpCallbackInfo const&);  // slot 7
};
}  // namespace gf

#endif
