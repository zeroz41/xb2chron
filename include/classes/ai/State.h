#ifndef CLASSES_AI_STATE_H
#define CLASSES_AI_STATE_H

namespace ai { class State; }

namespace ai {
// table none (its derived classes'); a state of a state machine (ai::Fsm, ai::Hfsm), made in one of the machine's
// state buffers by the function its machine registered for its ID
class State {
public:
    // the states' create functions construct it in their buffer: no ID yet, no next state
    State() : m_stateID(static_cast<unsigned int>(-1)), m_nextStateID(static_cast<unsigned int>(-1)), pad_10() {}
    // inline: a state's deleting destructor only frees it (StateFieldWallAiWait's)
    virtual ~State() {}  // slot 0
    virtual const char* getName() const = 0;  // slot 2
    virtual void onEnter(void*, ai::State*) = 0;  // slot 3
    virtual void onLeave(void*, ai::State*) = 0;  // slot 4
    virtual void onStep(void*, void const*) = 0;  // slot 5
    virtual void onEvent(void*, void*);  // slot 6
    // the ID its machine made it for (Fsm::setStateImpl sets it), and the one it asks its machine to change to,
    // -1 for none (Fsm::update changes to it after the state's step). The names are not the original's.
    unsigned int m_stateID;
    unsigned int m_nextStateID;
    unsigned char pad_10[0x8];  // fields: size from its derived classes
};
}  // namespace ai

#endif
