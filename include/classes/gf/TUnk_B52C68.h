#ifndef CLASSES_GF_TUNK_B52C68_H
#define CLASSES_GF_TUNK_B52C68_H

#include "classes/ai/State.h"
#include "classes/gf/IGfEvent.h"
#include <new>

namespace gf { class MapjumpCallbackInfo; enum GEV : int; }

namespace gf {
// table 0x7100B52C68 (no RTTI): an arena state (getName "StateArenaWait"; TUnk_B535D0's setup fn_7100291100 registers it
// as state 0, sizeof 0x28); its owner is TUnk_B535D0. Its slots and its key function gevMapjump (0x710028F250)
// are in unit_710028EBB0, which defines them; only the declarations are recovered here.
class TUnk_B52C68 : public ::ai::State, public ::gf::IGfEvent {
public:
    // what the arena's Fsm registers: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) TUnk_B52C68; }
    virtual ~TUnk_B52C68();  // slot 0
    virtual const char* getName() const;  // slot 2
    virtual void onEnter(void*, ai::State*);  // slot 3
    virtual void onLeave(void*, ai::State*);  // slot 4
    virtual void onStep(void*, void const*);  // slot 5
    virtual void gevMapjump(gf::GEV, gf::MapjumpCallbackInfo const&);  // slot 7

    // gevMapjump sets it for GEV 6 while the arena's local flag 0xDC0D is set; create leaves it as it is
    // (the name is not the original's)
    bool m_arenaFlagSeen;
};
}  // namespace gf

#endif
