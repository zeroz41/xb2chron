#ifndef CLASSES_GF_STATERESETBLADE_H
#define CLASSES_GF_STATERESETBLADE_H

#include "classes/ai/State.h"
#include <new>

namespace ai { class State; }

namespace gf {
// table 0x7100B56618
class StateResetBlade : public ::ai::State {
public:
    // what GfGameState::build registers with its Fsm: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) StateResetBlade(); }
    // inline: the deleting destructor only frees it
    virtual ~StateResetBlade() {}  // slot 0
    virtual const char* getName() const;  // slot 2
    virtual void onEnter(void*, ai::State*);  // slot 3
    virtual void onLeave(void*, ai::State*);  // slot 4
    virtual void onStep(void*, void const*);  // slot 5
};
}  // namespace gf

#endif
