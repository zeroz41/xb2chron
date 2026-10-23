#ifndef CLASSES_GF_STATEEVENT_H
#define CLASSES_GF_STATEEVENT_H

#include "classes/ai/State.h"
#include <new>

namespace ai { class State; }

namespace gf {
// table 0x7100B564B0
class StateEvent : public ::ai::State {
public:
    // what GfGameState::build registers with its Fsm: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) StateEvent(); }
    // inline: the deleting destructor only frees it
    virtual ~StateEvent() {}  // slot 0
    virtual const char* getName() const;  // slot 2
    virtual void onEnter(void*, ai::State*);  // slot 3
    virtual void onLeave(void*, ai::State*);  // slot 4
    virtual void onStep(void*, void const*);  // slot 5
};
}  // namespace gf

#endif
