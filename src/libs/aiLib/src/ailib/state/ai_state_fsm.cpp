#include "mm/mtl/FixedQueue.h"
#include "ai/Fsm.h"
#include "classes/ai/State.h"
#include "classes/mm/mtl/IAllocator.h"
#include "mm/MMStdBase.h"

namespace ai {

Fsm::Fsm(mm::mtl::IAllocator* allocator)
    : m_owner(nullptr), m_pState(nullptr), m_createFuncs(allocator), m_allocator(allocator), m_stateBuffer(nullptr),
      m_stateSize(0), m_setup(false), m_inside(false) {}

void Fsm::beginSetup(void* owner, unsigned int stateCount) {
#line 37
    MM_ASSERT(m_pState == nullptr);
    m_owner = owner;
    m_createFuncs.resize(stateCount, nullptr);
    m_setup = true;
}

void Fsm::endSetup() {
    m_setup = false;
    m_stateBuffer = m_allocator->allocate(m_stateSize * 2, 16);
    m_stateBufferQueue.push_back(m_stateBuffer);
    m_stateBufferQueue.push_back(static_cast<char*>(m_stateBuffer) + m_stateSize);
}

void Fsm::cleanup() {
    if (m_pState != nullptr) {
        m_pState->onLeave(m_owner, nullptr);
        m_pState->~State();
        m_stateBufferQueue.push_back(m_pState);
        m_pState = nullptr;
    }
    m_stateBufferQueue.clear();
    m_allocator->deallocate(m_stateBuffer);
}

void Fsm::setState(unsigned int stateID) {
#line 79
    MM_ASSERT(!m_inside);
    setStateImpl(stateID);
}

void Fsm::setStateImpl(unsigned int stateID) {
    State* prev = m_pState;
#line 93
    MM_ASSERT(m_createFuncs[stateID]);
#line 94
    MM_ASSERT(!m_stateBufferQueue.empty());
    void* buffer = m_stateBufferQueue.pop_front();
    m_pState = m_createFuncs[stateID](buffer);
    m_pState->m_stateID = stateID;
    State* next = m_pState;
    if (prev != nullptr) {
        prev->onLeave(m_owner, next);
        m_pState->onEnter(m_owner, prev);
        prev->~State();
        m_stateBufferQueue.push_back(prev);
    } else {
        next->onEnter(m_owner, nullptr);
    }
}

void Fsm::update(const void* arg) {
    m_inside = true;
    if (m_pState != nullptr) {
        m_pState->onStep(m_owner, arg);
        if (m_pState->m_nextStateID != static_cast<unsigned int>(-1)) {
            setStateImpl(m_pState->m_nextStateID);
        }
    }
    m_inside = false;
}

}  // namespace ai
