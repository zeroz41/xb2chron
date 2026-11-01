#include "classes/anm/Control.h"
#include "anm/AsmListener.h"

#include "anm/AsmBlender.h"
#include "anm/Factory.h"
#include "anm/Util.h"
#include "classes/anm/ResASM.h"
#include "classes/anm/ASMControl.h"

namespace anm {

AsmClip::AsmClip() : m_pControl(nullptr), m_pRes(nullptr) {}

AsmClip::~AsmClip() {
    destroyControl();
}

void AsmClip::destroyControl() {
    if (m_pControl != nullptr) {
        m_pControl->release();
        m_pControl = nullptr;
    }
    m_pRes = nullptr;
}

void AsmClip::createControl(const ResClipData& res, mm::mtl::IAllocator& allocator) {
    m_pControl = Factory::createControl(res.m_pBinding, &allocator);
    m_pRes = &res;
}

bool AsmClip::update(float dt, AsmListener* listener) {
    if (m_pControl == nullptr) {
        return true;
    }
    PlayMode mode = Util::getPlayMode(*m_pControl->m_pBinding);
    float prev = m_pControl->m_localTime;
    float time = prev + m_pControl->m_speed * dt;
    float local = Util::calcLocalTime(time, m_pRes->m_start, m_pRes->m_end, mode);
    m_pControl->setLocalTime(local);
    bool looped = time != local;
    bool isLoop = mode == PLAY_MODE_LOOP;
    bool reverse = m_pRes->m_pInfo->m_speed < 0.0f;
    bool loopedAround = looped && isLoop;
    if (listener != nullptr) {
        for (unsigned int i = 0; i < 5; ++i) {
            if (m_pRes->m_frameAnnotations[i].size() != 0) {
                CallBackDetector::executeFrame(*listener, prev, local, reverse, loopedAround,
                                               m_pRes->m_frameAnnotations[i]);
            }
        }
    }
    if (mode == PLAY_MODE_ONCE) {
        looped = time >= m_pRes->m_end + -0.0001f;
    }
    return looped;
}

void AsmClip::setLocalTime(float time) {
    if (m_pControl != nullptr) {
        m_pControl->setLocalTime(time);
    }
}

float AsmClip::getLocalTime() const {
    if (m_pControl != nullptr) {
        return m_pControl->m_localTime;
    }
    return 0.0f;
}

void AsmClip::setSpeed(float speed) {
    if (m_pControl != nullptr) {
        m_pControl->m_speed = m_pRes->m_pInfo->m_speed * speed;
    }
}

void AsmClip::setWeight(float weight) {
    if (m_pControl != nullptr) {
        m_pControl->m_weight = m_pRes->m_pInfo->m_weight * weight;
    }
}

ASMControl::ASMControl(const ResASM& res, mm::mtl::IAllocator& allocator)
    : ReferenceObject(&allocator), m_pRes(&res), m_variables(&allocator) {
    m_blender.setup(res, allocator);
    const ResStateArray* states = res.m_pStates;
    m_variables.resize(states->m_variables.size());
    for (unsigned int i = 0; i < states->m_variables.size(); ++i) {
        m_variables[i].setup(states->m_variables[i]);
    }
    StateMachine* pStateMachine = m_stateMachines;
    for (unsigned int i = 0; i < 7; ++i, ++pStateMachine) {
        pStateMachine->m_pBlender = &m_blender;
        pStateMachine->m_pVariables = &m_variables;
        pStateMachine->setup(res, i, allocator);
    }
    m_locomotion.m_translation = mm::Vec4::zero;
    m_locomotion.m_rotation = mm::Quat::identity;
    m_locomotion.m_scale = mm::Vec4::unit;
}

ASMControl::~ASMControl() {
    for (unsigned int i = 0; i < 7; ++i) {
        m_stateMachines[i].cleanup();
    }
    m_blender.cleanup();
}

void ASMControl::setListener(AsmListener* listener) {
    for (unsigned int i = 0; i < 7; ++i) {
        m_stateMachines[i].m_pListener = listener;
    }
}

void ASMControl::updateFrame(float dt) {
    for (unsigned int i = 0; i < 7; ++i) {
        m_stateMachines[i].update(dt);
    }
    m_blender.getDeltaExtractMotion(dt, &m_locomotion);
    for (unsigned int i = 0; i < 7; ++i) {
        m_stateMachines[i].updateFrame(dt);
    }
}

bool ASMControl::setVariable(const char* name, int value) {
    Variable* variable = findVariable(m_variables, name);
    if (variable == nullptr) {
        return false;
    }
    return variable->setValue(value);
}

bool ASMControl::setVariable(const char* name, float value) {
    Variable* variable = findVariable(m_variables, name);
    if (variable == nullptr) {
        return false;
    }
    return variable->setValue(value);
}

bool ASMControl::getVariable(const char* name, float* value) const {
    const Variable* variable = findVariable(m_variables, name);
    if (variable == nullptr) {
        return false;
    }
    return variable->getValue(value);
}

}  // namespace anm
