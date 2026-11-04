#ifndef CLASSES_GF_TUNK_B53370_H
#define CLASSES_GF_TUNK_B53370_H

#include "classes/ai/State.h"
#include <new>
namespace gf { class GfGameArena; }
namespace fw { class UpdateInfo; }
#include "classes/gf/IGfEvent.h"
#include "classes/gf/GfEvent.h"

namespace gf { class MapjumpCallbackInfo; enum GEV : int; }

namespace gf {
// table 0x7100B53370 (no RTTI): an arena state (getName "StateArenaEvent"; GfGameArena's setup registers it)
class StateArenaEvent : public ::ai::State, public ::gf::IGfEvent {
public:
    // what the arena's Fsm registers: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) StateArenaEvent; }
    virtual ~StateArenaEvent() {}  // slot 0
    virtual const char* getName() const { return "StateArenaEvent"; }  // slot 2
    virtual void onEnter(void* owner, ai::State* prev) { enter(static_cast<GfGameArena*>(owner), prev); }  // slot 3
    virtual void onLeave(void*, ai::State*) { GfEvent::removeEventCallback(this); }  // slot 4
    virtual void onStep(void*, void const*) {  // slot 5
        if (m_playState == 3) {
            requestState(4);
        }
    }
    // the key function (defined in the .cpp)
    virtual void gevMapjump(gf::GEV, gf::MapjumpCallbackInfo const&);  // slot 7
    virtual void gevPlayEvent(gf::GEV gev, unsigned int);  // slot 8
    // 2.0.0's symbols name it. A member because onEnter tail-calls it
    // with its own arguments. What it does (0x160 bytes, not written yet): adds the state as event callback,
    // reads GfArenaUtil::getPlayEvent, GfDataEvent::getEventZone, and GfPlayFactory::createMap... play commands.
    void enter(GfGameArena* arena, ai::State* prev);

    // 1/3/2 for GEV 0xC/0xD/0xE (gevPlayEvent); onStep asks for state 4 at 3 (the name is not the original's)
    int m_playState;
    unsigned char pad_24[0x4];
};
}  // namespace gf

#endif
