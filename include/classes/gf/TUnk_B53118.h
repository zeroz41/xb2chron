#ifndef CLASSES_GF_TUNK_B53118_H
#define CLASSES_GF_TUNK_B53118_H

#include "classes/ai/State.h"
#include <new>
#include "classes/gf/IGfEvent.h"
#include "classes/gf/GfEvent.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/TUnk_B52C38.h"
#include "classes/gf/TUnk_B535D0.h"
#include "btl/Utility.h"

namespace gf { class MapjumpCallbackInfo; enum GEV : int; }

namespace gf {
// Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them. Free functions: no class is proven for
// them; TUnk_B53118::onStep calls both each step, fn_71005661C0 with fn_71002AC5B8's answer. fn_71002AC5B8 sits
// in gf_game_manager's unit, fn_71005661C0 in gf_req_scom's.
unsigned int fn_71002AC5B8();  // returns TUnk_B535D0 +0x104 (0 when absent)
void fn_71005661C0(unsigned int value);  // takes fn_71002AC5B8's answer

// table 0x7100B53118 (no RTTI): an arena state (getName "StateArenaReturnBattle"; TUnk_B535D0's setup registers
// it); its owner is TUnk_B535D0
class TUnk_B53118 : public ::ai::State, public ::gf::IGfEvent {
public:
    // what the arena's Fsm registers: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) TUnk_B53118(); }
    virtual ~TUnk_B53118() {}  // slot 0
    virtual const char* getName() const { return "StateArenaReturnBattle"; }  // slot 2
    virtual void onEnter(void*, ai::State*) { GfEvent::addEventCallback(this); }  // slot 3
    virtual void onLeave(void*, ai::State*) {  // slot 4
        GfEvent::removeEventCallback(this);
        btl::Utility::fn_710000FB4C();
    }
    virtual void onStep(void* owner, void const*) {  // slot 5
        TUnk_B535D0* arena = static_cast<TUnk_B535D0*>(owner);
        fn_71005661C0(fn_71002AC5B8());
        arena->m_msgObj->fn_710028D4A4();
        GfMenuManager::fn_710035CE3C();
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
