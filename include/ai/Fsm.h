#ifndef AI_FSM_H
#define AI_FSM_H

#include "mm/mtl/FixedQueue.h"
#include "mm/mtl/Vector.h"
#include "mm/MMStdBase.h"

// aiLib's ai_state_fsm.h, as the including file's include path named it (the game's files' form is the one their
// citations show; the libs/ form is not seen yet)
#ifdef MM_LIB_FROM_LIBS
#define AI_STATE_FSM_PATH "../../src\\ailib/state/ai_state_fsm.h"
#else
#define AI_STATE_FSM_PATH "D:/Monolithsoft/BF2/prog/application/BF2//../../libs/ailib/src\\ailib/state/ai_state_fsm.h"
#endif

namespace mm { namespace mtl { class IAllocator; }}
namespace ai { class State; }

namespace ai {

// aiLib's finite state machine: one state at a time, made in one of two buffers in turn (the one the state it
// replaces leaves) by the function registered for its ID
class Fsm {
public:
    // makes a state in the buffer it is given
    typedef State* (*CreateFunc)(void* buffer);

    explicit Fsm(mm::mtl::IAllocator* allocator);
    // starts a setup of stateCount states for owner (the states' functions get it)
    void beginSetup(void* owner, unsigned int stateCount);
    // registers T (its create function) for stateID during a setup, growing the state buffers to hold it (inline:
    // TaskFieldWallPrepare::onCreate shows it)
    template <typename T>
    void registerState(unsigned int stateID) {
#line 31 AI_STATE_FSM_PATH
        MM_ASSERT(m_setup);
        m_createFuncs[stateID] = &T::create;
        const unsigned long stateSize = sizeof(T);
        const unsigned long& size = m_stateSize > stateSize ? m_stateSize : stateSize;
        m_stateSize = (size + 15) & ~15ul;
    }
    // allocates the two state buffers, m_stateSize bytes each
    void endSetup();
    void cleanup();
    void setState(unsigned int stateID);
    void update(const void* arg);

private:
    void setStateImpl(unsigned int stateID);

public:
    // (the field names are the original's where its assertions name them, else not the original's)
    void* m_owner;
    State* m_pState;
    mm::mtl::Vector<CreateFunc> m_createFuncs;
    mm::mtl::FixedQueue<void*, 2> m_stateBufferQueue;
    mm::mtl::IAllocator* m_allocator;
    void* m_stateBuffer;     // endSetup's: both state buffers
    unsigned long m_stateSize;  // a state buffer's size
    bool m_setup;            // set by beginSetup, cleared by endSetup
    bool m_inside;           // set while update steps the state: setState asserts it is not
};

}  // namespace ai

#endif
