#ifndef CLASSES_AI_STATE_H
#define CLASSES_AI_STATE_H

#include "mm/MMStdBase.h"

// ailib's ai_state.h, as the game's include path names it
#define AI_STATE_H_PATH "D:/Monolithsoft/BF2/prog/application/BF2//../../libs/ailib/src\\ailib/state/ai_state.h"

namespace ai { class State; }

namespace ai {
// table none (its derived classes'); a state of a state machine (ai::Fsm, ai::Hfsm), made in one of the machine's
// state buffers by the function its machine registered for its ID
class State {
public:
    // the states' create functions construct it in their buffer: no ID yet, no next state
    // no state (ai_state.h's assertion names it)
    enum : unsigned int { INVALID_STATE_ID = 0xFFFFFFFFu };

    State() : m_stateID(static_cast<unsigned int>(-1)), m_reqState(static_cast<unsigned int>(-1)), pad_10() {}
    // inline: a state's deleting destructor only frees it (StateFieldWallAiWait's)
    virtual ~State() {}  // slot 0
    virtual const char* getName() const = 0;  // slot 2
    virtual void onEnter(void*, ai::State*) = 0;  // slot 3
    virtual void onLeave(void*, ai::State*) = 0;  // slot 4
    virtual void onStep(void*, void const*) = 0;  // slot 5
    virtual void onEvent(void*, void*);  // slot 6
    // asks its machine to change to state id after this step; one request per step (inline: the PC's wall states
    // inline it with ai_state.h's assertion; the name is not the original's)
    void requestState(unsigned int id) {
#line 51 AI_STATE_H_PATH
        MM_ASSERT(m_reqState == INVALID_STATE_ID);
        m_reqState = id;
    }
    // the ID its machine made it for (Fsm::setStateImpl sets it), and the one it asks its machine to change to,
    // -1 for none (Fsm::update changes to it after the state's step). m_stateID's name is not the original's;
    // m_reqState is ai_state.h's (its assertion `m_reqState == INVALID_STATE_ID`).
    unsigned int m_stateID;
    unsigned int m_reqState;
    unsigned char pad_10[0x8];  // fields: size from its derived classes
};
}  // namespace ai

#endif
