#include "classes/fw/Framework.h"
#include "classes/fw/IPauseTrigger.h"
#include "classes/ml/WorkCpu.h"
#include "classes/fw/Framework.h"
#include "classes/fw/IPauseTrigger.h"
#include "classes/fw/FrameworkMemory.h"
#include "classes/fw/ManagerRegister.h"
#include "classes/fw/TransformManager.h"
#include "classes/ml/Thread.h"
#include "classes/ml/WorkCpu.h"

namespace fw {

Framework::~Framework() {
    m_threadExit = true;
    m_threadEvent.setSignal(true);
    while (!m_thread->isTerminated()) {
    }
    if (m_thread != nullptr) {
        m_thread->release();
        m_thread = nullptr;
    }
    destroyManager();
}

mm::mtl::IAllocator* Framework::getAllocator() {
    Framework* framework = get();
    return framework == nullptr ? nullptr : &framework->m_allocator;
}

void Framework::prepareEnter() {
    m_state = 3;
}

void Framework::prepareExit() {}

void Framework::activate() {
    for (IPauseTrigger* trigger : m_pauseTriggers) {
        trigger->activate();
    }
}

void Framework::deactivate() {
    for (IPauseTrigger* trigger : m_pauseTriggers) {
        trigger->deactivate();
    }
}

void Framework::fn_710018369C(const fw::UpdateInfo& info) {
    m_threadEvent.setSignal(true);
}

void Framework::fn_71001836A8() {
    while (m_threadEvent.isSignal()) {
    }
}

void Framework::fn_71001836D0(bool flag) {
    m_threadFlag = flag;
}

void Framework::enterFinalizeApplet() {
    ManagerRegister::get()->enterFinalizeApplet();
}

mtl::ALLOC_HANDLE Framework::getMemHandle() {
    Framework* framework = get();
    if (framework == nullptr) {
        return mtl::ALLOC_HANDLE();
    }
    if (framework->m_memHandle.m_handle == 0) {
        return FrameworkMemory::getMem(5);
    }
    return framework->m_memHandle;
}

void Framework::setUpdateSpeed(float speed) {
    Framework* framework = get();
    if (framework != nullptr) {
        framework->m_updateSpeed = speed;
    }
}

void Framework::setLayerUpdateSpeed(unsigned int layer, float speed) {
    Framework* framework = get();
    if (framework != nullptr) {
        framework->m_layers[layer].m_speedRequest = speed;
    }
}

float Framework::getLayerUpdateSpeed(unsigned int layer) {
    Framework* framework = get();
    if (framework != nullptr) {
        return framework->m_layers[layer].m_speed;
    }
    return 1.0f;
}

void Framework::setLayerPause(unsigned int layer, bool pause) {
    Framework* framework = get();
    if (framework != nullptr) {
        framework->m_layers[layer].m_pauseRequest = pause;
    }
}

bool Framework::isLayerPause(unsigned int layer) {
    Framework* framework = get();
    if (framework != nullptr) {
        return framework->m_layers[layer].m_pause;
    }
    return false;
}

unsigned int Framework::getFrameCount() {
    return ml::WorkCpu::getFrameCount();
}

// the pause triggers' search (the original's find over the vector, as its loop shows)
static inline IPauseTrigger** findPauseTrigger(mm::mtl::FixedVector<IPauseTrigger*, 32>& triggers,
                                               IPauseTrigger* trigger) {
    IPauseTrigger** it = triggers.begin();
    IPauseTrigger** end = triggers.end();
    for (; it != end; ++it) {
        if (*it == trigger) {
            break;
        }
    }
    return it;
}

void Framework::addPauseCallback(IPauseTrigger* trigger) {
    Framework* framework;
    if (trigger != nullptr && (framework = get()) != nullptr) {
        if (findPauseTrigger(framework->m_pauseTriggers, trigger) == framework->m_pauseTriggers.end()) {
            framework->m_pauseTriggers.push_back(trigger);
        }
    }
}

void Framework::removePauseCallback(IPauseTrigger* trigger) {
    Framework* framework = get();
    if (framework != nullptr) {
        IPauseTrigger** it = findPauseTrigger(framework->m_pauseTriggers, trigger);
        if (it != framework->m_pauseTriggers.end()) {
            framework->m_pauseTriggers.erase(it);
        }
    }
}

IPauseTrigger::IPauseTrigger() {
    Framework::addPauseCallback(this);
}

IPauseTrigger::~IPauseTrigger() {
    Framework::removePauseCallback(this);
}

TransformManager::~TransformManager() {}

}  // namespace fw
