#include "mm/mtl/Queue.h"
#include "mm/mtl/FixedQueue.h"
#include "classes/ai/State.h"
#include "ai/Hfsm.h"

#include "classes/mm/mtl/IAllocator.h"
#include "mm/MMStdBase.h"

namespace ai {

Hfsm::Hfsm(mm::mtl::IAllocator* allocator)
    : m_owner(nullptr), m_pState(nullptr), m_stateInfos(allocator), m_stateBufferQueue(allocator),
      m_allocator(allocator), m_stateBuffer(nullptr), m_stateSize(0), m_setup(false), m_inside(false) {}

void Hfsm::beginSetup(void* owner, unsigned int stateCount, unsigned int maxDepth) {
#line 39
    MM_ASSERT(m_pState == nullptr);
#line 40
    MM_ASSERT(maxDepth <= MAX_DEPTH);
    m_owner = owner;
    m_stateInfos.resize(stateCount);
    m_stateBufferQueue.reserve(maxDepth * 2, m_stateBufferQueue.defaultAlignment());
    m_setup = true;
}

void Hfsm::endSetup() {
    m_setup = false;
    unsigned int count = m_stateBufferQueue.capacity();
    char* buffer = static_cast<char*>(m_allocator->allocate(m_stateSize * count, 16));
    m_stateBuffer = buffer;
    for (unsigned int i = 0; i < count; i++) {
        m_stateBufferQueue.push_back_fixed(buffer);
        buffer += m_stateSize;
    }
}

void Hfsm::cleanup() {
    clearState();
    m_stateBufferQueue.clear();
    m_allocator->deallocate(m_stateBuffer);
}

void Hfsm::clearState() {
    if (m_pState != nullptr) {
        for (State* state = m_pState; state != nullptr; state = state->m_pParent) {
            state->onLeave(m_owner, nullptr);
        }
        for (State* state = m_pState; state != nullptr;) {
            State* parent = state->m_pParent;
            state->~State();
            void* buffer = state;
            m_stateBufferQueue.push_back(buffer);
            state = parent;
        }
    }
    m_pState = nullptr;
}

void Hfsm::setState(unsigned int stateID) {
#line 87
    MM_ASSERT(!m_inside);
    setStateImpl(stateID);
}

// setStateImpl (0x7100865950) is not matched yet: leaves the old chain below the states both chains share, makes and
// enters the new one

void Hfsm::update(const void* arg) {
    m_inside = true;
    mm::mtl::FixedQueue<State*, MAX_DEPTH> chain;
    for (State* state = m_pState; state != nullptr; state = state->m_pParent) {
        chain.push_front(state);
    }
    for (mm::mtl::FixedQueue<State*, MAX_DEPTH>::iterator it = chain.begin(); it != chain.end(); ++it) {
        (*it)->onStep(m_owner, arg);
        if ((*it)->m_reqState != State::INVALID_STATE_ID) {
            break;
        }
    }
    for (mm::mtl::FixedQueue<State*, MAX_DEPTH>::iterator it = chain.begin(); it != chain.end(); ++it) {
        unsigned int reqState = (*it)->m_reqState;
        if (reqState != State::INVALID_STATE_ID) {
            (*it)->m_reqState = State::INVALID_STATE_ID;
            setStateImpl(reqState);
            break;
        }
    }
    m_inside = false;
}

bool Hfsm::execEvent(void* event) {
    m_inside = true;
    for (State* state = m_pState; state != nullptr; state = state->m_pParent) {
        if (state->onEvent(m_owner, event)) {
            if (state->m_reqState != State::INVALID_STATE_ID) {
                setStateImpl(state->m_reqState);
            }
            m_inside = false;
            return true;
        }
    }
    m_inside = false;
    return false;
}

}  // namespace ai
