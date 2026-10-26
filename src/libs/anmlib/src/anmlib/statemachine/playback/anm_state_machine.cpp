#include "anm/StateMachine.h"
#include "anm/AsmBlender.h"
#include "classes/anm/ReferenceObject.h"
#include "classes/anm/ResASM.h"
#include "classes/anm/SimplexState.h"
#include "classes/anm/FrozenState.h"
#include "classes/anm/LerpBlendTree.h"
#include "classes/anm/SpeedLerpBlendTree.h"
#include "classes/anm/AddBlendTree.h"
#include "classes/anm/LerpAddBlendTree.h"
#include "anm/Array.h"
#include <new>
#include <float.h>
#include "mm/MMStdBase.h"
#include "mm/mtl/IntrusivePtr.h"
#include "mm/mtl/Map.h"
#include "mm/mtl/MTRand.h"
#include "nn/os.h"

#define ANM_STATE_MACHINE_PATH "D:/Monolithsoft/BF2/prog/libs/anmlib/src/anmlib/statemachine/playback/anm_state_machine.cpp"

namespace anm {

StateMachine::StateMachine() : m_interpolate(nullptr), m_elapsed(0.0f), m_pListener(nullptr), m_pBlender(nullptr), m_pVariables(nullptr),
      m_pAllocator(nullptr) {}

StateMachine::~StateMachine() {}

AsmState* StateMachine::createState(const ResStateData& res) {
    switch (res.m_pInfo->m_type) {
    case 0:
        return new (m_pAllocator->allocate(sizeof(SimplexState), 8)) SimplexState(&res, *m_pAllocator);
    case 1:
        return new (m_pAllocator->allocate(sizeof(FrozenState), 8)) FrozenState(&res, *m_pAllocator);
    case 2: {
        const ResBlendTree* pTree = res.m_pInfo->m_pTree;
        switch (pTree->m_type) {
        case 0:
            return new (m_pAllocator->allocate(sizeof(LerpBlendTree), 8)) LerpBlendTree(
                &res, static_cast<const ResLerpTree*>(pTree), *m_pVariables, *m_pAllocator);
        case 2:
            return new (m_pAllocator->allocate(sizeof(SpeedLerpBlendTree), 8)) SpeedLerpBlendTree(
                &res, static_cast<const ResSpeedLerpTree*>(pTree), *m_pVariables, *m_pAllocator);
        case 3:
            return new (m_pAllocator->allocate(sizeof(AddBlendTree), 8)) AddBlendTree(
                &res, static_cast<const ResAddTree*>(pTree), *m_pVariables, *m_pAllocator);
        case 4:
            return new (m_pAllocator->allocate(sizeof(LerpAddBlendTree), 8)) LerpAddBlendTree(
                &res, static_cast<const ResLerpAddTree*>(pTree), *m_pVariables, *m_pAllocator);
        default:
#line 754 ANM_STATE_MACHINE_PATH
            MM_ASSERT(0);
            return nullptr;
        }
    }
    default:
#line 760 ANM_STATE_MACHINE_PATH
        MM_ASSERT(0);
        return nullptr;
    }
}

void StateMachine::updateFrame(float dt) {
    float rest = 0.0f;
    if (m_pState) {
        float before = m_pState->getLocalTime();
        rest = m_pState->m_speed * dt;
        m_pState->update(dt, m_pListener);
        rest -= m_pState->getLocalTime() - before;
    }
    if (m_pPrevState && m_interpolate->m_type == 1) {
        m_pPrevState->update(dt, m_pListener);
    }
    if (isEnd()) {
        if (const ResLoopCount* pNext = m_pState->m_pRes->m_pInfo->m_pLoopCount) {
            doTrans(pNext->m_pNextState, pNext->m_trans, pNext->m_interpolate, 0.0f, rest);
        }
    }
    if (m_additives.m_tree.m_size != 0) {
        for (AdditiveMap::node* n = m_additives.m_tree.first(); n != nullptr; n = m_additives.m_tree.next(n)) {
            n->value.second.updateFrame(dt, m_pListener);
        }
    }
}

bool StateMachine::doTrans(const char* state, const TransInfo& trans, const InterpolateInfo& interpolate, float time,
                           float frame) {
    StateMap::node* n = m_states.find(state);
    if (n == nullptr) {
        return false;
    }
    if (!m_pPrevState) {
        m_pState->onLeave(m_pListener);
        m_pPrevState = m_pState;
    } else if (m_pPrevState->m_weight > 0.5f) {
        m_pState->onLeave(m_pListener);
        m_pState->dettach(m_pBlender);
    } else {
        m_pPrevState->dettach(m_pBlender);
        m_pState->onLeave(m_pListener);
        m_pPrevState = m_pState;
    }
    AsmState* pState = n->value.second.get();
    if (pState->getRefCount() > 1) {
        pState = createState(*pState->m_pRes);
    }
    m_pState = pState;
    float start;
    switch (trans.m_type) {
    case 0:
        start = trans.m_frame + frame;
        break;
    case 1:
        start = m_pPrevState->getLocalTime();
        break;
    case 2:
        start = trans.m_frame + trans.m_range * rand();
        break;
    case 3:
        start = m_pPrevState->getLocalTime() - time;
        break;
    default:
        start = 0.0f;
        break;
    }
    m_pState->setLocalTime(start);
    if (interpolate.m_time <= FLT_EPSILON) {
        m_pPrevState->dettach(m_pBlender);
        m_pPrevState = nullptr;
        m_pState->setWeight(1.0f);
        m_interpolate = nullptr;
    } else {
        m_pState->setWeight(0.0f);
        m_pPrevState->setWeight(1.0f);
        m_interpolate = &interpolate;
    }
    m_elapsed = 0.0f;
    m_pState->attach(m_pBlender);
    m_pState->onEnter(m_pListener);
    return true;
}

// inline: its static is reached through the GOT, and it sits after clearState, its first user's callee
inline float rand() {
    static mm::mtl::MTRand sRand(nn::os::GetSystemTick().GetInt64Value());
    if (--sRand.m_left <= 0) {
        sRand.nextMt();
    }
    unsigned int y = *sRand.m_next++;
    y ^= y >> 11;
    y ^= (y << 7) & 0x9d2c5680;
    y ^= (y << 15) & 0xefc60000;
    y ^= y >> 18;
    return y * (1.0 / 4294967296.0);
}

bool StateMachine::setState(const char* state, StartFrameType type) {
    StateMap::node* n = m_states.find(state);
    if (n == nullptr) {
        return false;
    }
    clearState();
    AsmState* pState = n->value.second.get();
#line 358 ANM_STATE_MACHINE_PATH
    MM_ASSERT(pState->getRefCount() == 1);
    m_pState = pState;
    float frame = 0.0f;
    if (AsmClip* clip = m_pState->getBaseClip()) {
        const ResClipData* res = clip->m_pRes;
        if (type == 0) {
            frame = res->m_start;
        } else if (type == 1) {
            frame = res->m_start + res->m_end * rand();
        }
    }
    m_pState->setLocalTime(frame);
    m_pState->setWeight(1.0f);
    m_pState->attach(m_pBlender);
    m_pState->onEnter(m_pListener);
    return true;
}

void StateMachine::clearState() {
    if (m_pPrevState) {
        m_pPrevState->onLeave(m_pListener);
        m_pPrevState->dettach(m_pBlender);
        m_pPrevState = nullptr;
    }
    if (m_pState) {
        m_pState->onLeave(m_pListener);
        m_pState->dettach(m_pBlender);
        m_pState = nullptr;
    }
    m_interpolate = nullptr;
    m_elapsed = 0.0f;
}

const char* StateMachine::getStateName() const {
    if (m_pState) {
        return m_pState->m_pRes->m_pInfo->m_name;
    }
    return nullptr;
}

unsigned long StateMachine::getAttribute(unsigned int category) const {
    if (!m_pState) {
        return 0;
    }
    const ResStateData* res = m_pState->m_pRes;
    if (category == 0) {
        return res->m_pInfo->m_attribute;
    }
    return res->m_attributes[category - 1];
}

bool StateMachine::isEnd() const {
    if (m_pState) {
        int loopCount = m_pState->m_loopCount;
        bool done = m_pState->m_loop >= loopCount;
        return loopCount != 0 && done;
    }
    return false;
}

bool StateMachine::isLoop() const {
    if (m_pState) {
        return m_pState->m_loopCount == 0;
    }
    return false;
}

void StateMachine::setLocalTime(float time) {
    if (m_pState) {
        m_pState->setLocalTime(time);
    }
}

float StateMachine::getLocalTime() const {
    if (m_pState) {
        return m_pState->getLocalTime();
    }
    return 0.0f;
}

void StateMachine::setSpeed(float speed) {
    if (AsmState* pState = m_pState.get()) {
        pState->m_speed = speed;
        pState->onSetSpeed();
    }
    if (AsmState* pState = m_pPrevState.get()) {
        pState->m_speed = speed;
        pState->onSetSpeed();
    }
}

float StateMachine::getSpeed() const {
    if (m_pState) {
        return m_pState->m_speed;
    }
    return 0.0f;
}

bool StateMachine::doEaseOutAdditive(const char* state, float time, InterpolateType type, InterpolateCurve curve) {
    AdditiveMap::node* n = m_additives.find(state);
    if (n == nullptr) {
        return false;
    }
    n->value.second.easeOut(m_pBlender, m_pListener, time, type, curve);
    return true;
}

bool StateMachine::setAdditiveStateSpeed(const char* state, float speed) {
    AdditiveMap::node* n = m_additives.find(state);
    if (n == nullptr) {
        return false;
    }
    if (AsmState* pState = n->value.second.m_state.get()) {
        pState->m_speed = speed;
        pState->onSetSpeed();
    }
    return true;
}

}  // namespace anm
