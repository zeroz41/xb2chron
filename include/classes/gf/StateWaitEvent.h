#ifndef CLASSES_GF_STATEWAITEVENT_H
#define CLASSES_GF_STATEWAITEVENT_H

#include "classes/ai/State.h"
#include <new>

namespace ai { class State; }

namespace gf {
// table 0x7100B561E0
class StateWaitEvent : public ::ai::State {
public:
    // what GfGameState::build registers with its Fsm: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) StateWaitEvent(); }
    // inline: the deleting destructor only frees it
    virtual ~StateWaitEvent() {}  // slot 0
    virtual const char* getName() const;  // slot 2
    virtual void onEnter(void*, ai::State*);  // slot 3
    virtual void onLeave(void*, ai::State*);  // slot 4
    virtual void onStep(void*, void const*);  // slot 5
};
}  // namespace gf

#endif
