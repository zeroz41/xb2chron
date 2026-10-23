#ifndef AI_HFSM_H
#define AI_HFSM_H

#include "mm/mtl/Queue.h"
#include "mm/mtl/Vector.h"
#include "mm/MMStdBase.h"

// aiLib's ai_state_hfsm.h, as the including file's include path named it (the game's files' form is the one their
// citations show; the libs/ form is not seen yet)
#ifdef MM_LIB_FROM_LIBS
#define AI_STATE_HFSM_PATH "../../src\\ailib/state/ai_state_hfsm.h"
#else
#define AI_STATE_HFSM_PATH "D:/Monolithsoft/BF2/prog/application/BF2//../../libs/ailib/src\\ailib/state/ai_state_hfsm.h"
#endif

namespace mm { namespace mtl { class IAllocator; }}
namespace ai { class State; }

namespace ai {

// aiLib's hierarchical finite state machine: a chain of states from a root to the current leaf, each made in a state
// buffer of its own by the function registered for its ID, each registered under a parent ID (the field names are
// the original's where its assertions name them, else not the original's)
class Hfsm {
public:
    // makes a state in the buffer it is given
    typedef State* (*CreateFunc)(void* buffer);
    // the deepest chain of states (hfsm.cpp asserts `maxDepth <= MAX_DEPTH`)
    enum { MAX_DEPTH = 8 };

    // a registered state: its create function and its parent's ID, -1 for a root (0x10 bytes)
    struct StateInfo {
        StateInfo() : createFunc(nullptr), parentID(static_cast<unsigned int>(-1)) {}
        CreateFunc createFunc;  // hfsm.cpp asserts `m_stateInfos[stateID].createFunc`
        unsigned int parentID;
    };

    explicit Hfsm(mm::mtl::IAllocator* allocator);
    // starts a setup of stateCount states for owner, chains of at most maxDepth states
    void beginSetup(void* owner, unsigned int stateCount, unsigned int maxDepth);
    // registers T, made by T::create, as state stateID under the state parentID (-1: a root); every state buffer
    // holds the largest registered state
    template <class T>
    void registerState(unsigned int stateID, int parentID) {
#line 50 AI_STATE_HFSM_PATH
        MM_ASSERT(m_setup);
        m_stateInfos[stateID].createFunc = &T::create;
        m_stateInfos[stateID].parentID = parentID;
        const unsigned long stateSize = sizeof(T);
        const unsigned long& size = m_stateSize > stateSize ? m_stateSize : stateSize;
        m_stateSize = (size + 15) & ~15ul;
    }
    // allocates the state buffers, m_stateSize bytes each, one per place of the buffer queue
    void endSetup();
    void cleanup();
    // leaves and destroys every state of the chain
    void clearState();
    void setState(unsigned int stateID);
    // steps the chain from its root until a state asks for another, then changes to it
    void update(const void* arg);
    // offers event to the chain from its leaf until a state handles it; false when none does
    bool execEvent(void* event);

private:
    void setStateImpl(unsigned int stateID);

public:
    void* m_owner;
    State* m_pState;  // the leaf; hfsm.cpp asserts `m_pState == nullptr`
    mm::mtl::Vector<StateInfo> m_stateInfos;
    mm::mtl::Queue<void*> m_stateBufferQueue;  // the free state buffers
    mm::mtl::IAllocator* m_allocator;
    void* m_stateBuffer;        // endSetup's: every state buffer
    unsigned long m_stateSize;  // a state buffer's size
    bool m_setup;               // set by beginSetup, cleared by endSetup
    bool m_inside;              // set while a state steps or handles an event: setState asserts `!m_inside`
};

}  // namespace ai

#endif
