#include "anm/Util.h"
#include "anm/Factory.h"
#include "classes/anm/ResASM.h"
#include "anm/StateMachine.h"
#include "classes/anm/ASMControl.h"
#include "gf/CallBackCache.h"
#include "classes/fw/AnimAsmUpdater.h"
#include "classes/fw/AnimAsmPoseSampler.h"
#include "classes/gf/GfComAsm.h"
#include "classes/gf/GfComAsm/AsmLisener.h"
#include "classes/gf/GfComAsm/ViewerListener.h"
#include <string.h>
#include "classes/fw/AnimationManager.h"
#include "classes/fw/UpdatableObject.h"
#include "classes/gf/GfAllocator.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/Quat.h"
#include "mm/Vec3.h"
#include "classes/gf/GfComModel.h"

namespace gf {

GfComAsm::GfComAsm()
    : m_control(nullptr), m_caches(getAllocator(ALLOCATOR(0))), m_pViewer(nullptr) {
    // in the body: the original stores the owners after the tables
    m_asmListener.m_owner = this;
    m_viewerListener.m_pOwner = this;
}

GfComAsm::~GfComAsm() {}

void GfComAsm::setup(const SetupInfo& info) {
    if (info.m_res == nullptr) {
        return;
    }
    GfComModel* model = m_owner->getComponent<GfComModel>(1);
    if (model == nullptr) {
        return;
    }
    anm::Pose* pose = model->m_pose;
    if (pose == nullptr) {
        return;
    }
    anm::ExtraTruckBuffer* extra = model->m_extraTruckBuffer;
    m_control = anm::Factory::createASMControl(*info.m_res, *getAllocator(ALLOCATOR(7)));
    if (m_control != nullptr) {
        m_control->setListener(&m_asmListener);
        if (info.m_state != nullptr) {
            m_control->m_stateMachines[0].setState(info.m_state, anm::StartFrameType(info.m_startFrame));
        }
        if (fw::AnimationManager* manager = mm::mtl::PtrSingleton<fw::AnimationManager>::get()) {
            m_updater.bind(m_control);
            if (m_updater.isBind()) {
                manager->addControlUpdater(getLayer(), m_updater);
            }
            fw::AnimAsmPoseSampler& sampler = m_sampler;
            sampler.m_sampleFlag = info.m_sampleFlag;
            sampler.bind(m_control, pose, extra);
            if (sampler.isBind()) {
                manager->addPoseSampler(getLayer(), sampler);
            }
        }
    }
    m_caches.reserve(32, 8);
}

void GfComAsm::cleanup() {
    m_caches.clear();
    if (m_control == nullptr) {
        return;
    }
    if (fw::AnimationManager* manager = mm::mtl::PtrSingleton<fw::AnimationManager>::get()) {
        if (m_sampler.isBind()) {
            manager->removePoseSampler(getLayer(), m_sampler);
            m_sampler.unbind();
        }
        if (m_updater.isBind()) {
            manager->removeControlUpdater(getLayer(), m_updater);
            m_updater.unbind();
        }
    }
    if (m_control != nullptr) {
        m_control->release();
        m_control = nullptr;
    }
}

const anm::ResASM* GfComAsm::getResource() const {
    if (m_control != nullptr) {
        return m_control->m_pRes;
    }
    return nullptr;
}

bool GfComAsm::getPlaybackTime(const char* state, float* pTime) const {
    if (const anm::ResASM* res = getResource()) {
        return anm::Util::getAsmPlaybackTime(*res, state, 0, pTime);
    }
    return false;
}

bool GfComAsm::getLocomotionReference(const char* state, float time, anm::QsTransform* pOut) const {
    if (const anm::ResASM* res = getResource()) {
        return anm::Util::getAsmLocomotionReference(*res, state, time, 0, pOut);
    }
    return false;
}

bool GfComAsm::getLocomotionDeltaReference(const char* state, float time, float dt, anm::QsTransform* pOut) const {
    if (const anm::ResASM* res = getResource()) {
        return anm::Util::getAsmLocomotionDeltaReference(*res, state, time, dt, 0, pOut);
    }
    return false;
}

bool GfComAsm::getClipInvFps(const char* state, unsigned int index, float* invFps) const {
    if (const anm::ResASM* res = getResource()) {
        if (const anm::Binding* binding = anm::Util::getAsmBinding(*res, state, index)) {
            *invFps = anm::Util::getInvFps(*binding);
            return true;
        }
    }
    return false;
}

const void* GfComAsm::getAppendix(const char* name) const {
    if (const anm::ResASM* res = getResource()) {
        if (const anm::ResAppendix* appendix = anm::Util::findAppendix(*res, name)) {
            return appendix->m_data;
        }
    }
    return nullptr;
}

bool GfComAsm::existState(const char* state) {
    if (const anm::ResASM* res = getResource()) {
        if (res->findResStateData(state) != nullptr) {
            return true;
        }
    }
    return false;
}

void GfComAsm::executeCallback() {
    for (unsigned int i = 0; i < m_caches.size(); ++i) {
        const anm::AsmAnnotetion* event = m_caches[i].m_event;
        bool handled = false;
        for (int j = 1; j < 5; ++j) {
            if (m_callbacks[j].delegate.isValid() && strcmp(m_callbacks[j].name, event->m_name) == 0) {
                m_callbacks[j].delegate(this, m_caches[i]);
                handled = true;
                break;
            }
        }
        if (!handled && m_callbacks[0].delegate.isValid()) {
            m_callbacks[0].delegate(this, m_caches[i]);
        }
    }
    m_caches.clear();
}

bool GfComAsm::execCmd(const char* cmd, AnimLayer layer) {
    if (layer <= 6 && m_control != nullptr) {
        return m_control->m_stateMachines[layer].executeCmd(cmd);
    }
    return false;
}

const char* GfComAsm::getStateName(AnimLayer layer) const {
    if (layer <= 6 && m_control != nullptr) {
        return m_control->m_stateMachines[layer].getStateName();
    }
    return nullptr;
}

bool GfComAsm::setState(const char* state, AnimLayer layer) {
    if (layer <= 6 && m_control != nullptr) {
        return m_control->m_stateMachines[layer].setState(state, anm::StartFrameType(0));
    }
    return false;
}

bool GfComAsm::easeIn(const char* state, float time, AnimLayer layer) {
    if (layer <= 6 && m_control != nullptr) {
        return m_control->m_stateMachines[layer].doEaseInAdditive(state, time, 1.0f, anm::InterpolateType(1),
                                                                  anm::InterpolateCurve(0));
    }
    return false;
}

bool GfComAsm::easeOut(const char* state, float time, AnimLayer layer) {
    if (layer <= 6 && m_control != nullptr) {
        return m_control->m_stateMachines[layer].doEaseOutAdditive(state, time, anm::InterpolateType(1),
                                                                   anm::InterpolateCurve(0));
    }
    return false;
}

bool GfComAsm::isActiveAdditiveState(const char* state, AnimLayer layer) {
    if (layer <= 6 && m_control != nullptr) {
        return m_control->m_stateMachines[layer].isActiveAdditiveState(state);
    }
    return false;
}

bool GfComAsm::setWeightAdditiveState(const char* state, float weight, AnimLayer layer) {
    if (layer <= 6 && m_control != nullptr) {
        return m_control->m_stateMachines[layer].setAdditiveStateWeight(state, weight);
    }
    return false;
}

bool GfComAsm::setSpeedAdditiveState(const char* state, float speed, AnimLayer layer) {
    if (layer <= 6 && m_control != nullptr) {
        return m_control->m_stateMachines[layer].setAdditiveStateSpeed(state, speed);
    }
    return false;
}

bool GfComAsm::isEnd(AnimLayer layer) const {
    if (layer <= 6 && m_control != nullptr) {
        return m_control->m_stateMachines[layer].isEnd();
    }
    return false;
}

bool GfComAsm::isLoop(AnimLayer layer) const {
    if (layer <= 6 && m_control != nullptr) {
        return m_control->m_stateMachines[layer].isLoop();
    }
    return false;
}

bool GfComAsm::isInterpolate(AnimLayer layer) const {
    return m_control != nullptr && layer <= 6 && m_control->m_stateMachines[layer].isInterpolate();
}

void GfComAsm::setLocalTime(float time, AnimLayer layer) {
    if (layer <= 6 && m_control != nullptr) {
        m_control->m_stateMachines[layer].setLocalTime(time);
    }
}

float GfComAsm::getLocalTime(AnimLayer layer) const {
    if (layer <= 6 && m_control != nullptr) {
        return m_control->m_stateMachines[layer].getLocalTime();
    }
    return 0.0f;
}

void GfComAsm::setSpeed(float speed, AnimLayer layer) {
    if (layer <= 6 && m_control != nullptr) {
        m_control->m_stateMachines[layer].setSpeed(speed);
    }
}

float GfComAsm::getSpeed(AnimLayer layer) const {
    if (layer <= 6 && m_control != nullptr) {
        return m_control->m_stateMachines[layer].getSpeed();
    }
    return 0.0f;
}

unsigned long GfComAsm::getAttribute(AsmCategory category, AnimLayer layer) const {
    if (layer <= 6 && m_control != nullptr) {
        return m_control->m_stateMachines[layer].getAttribute(category);
    }
    return 0;
}

const anm::QsTransform* GfComAsm::getLocomotion() const {
    if (m_control != nullptr) {
        return &m_control->m_locomotion;
    }
    static const anm::QsTransform s_identity = {
        mm::Vec4(mm::Vec3::zero.x, mm::Vec3::zero.y, mm::Vec3::zero.z, 1.0f),
        mm::Quat::identity,
        mm::Vec4(mm::Vec3::unit.x, mm::Vec3::unit.y, mm::Vec3::unit.z, 1.0f),
    };
    return &s_identity;
}

void GfComAsm::setVariable(const char* name, float value) {
    if (m_control != nullptr) {
        m_control->setVariable(name, value);
    }
}

void GfComAsm::getVariable(const char* name, float* value) const {
    if (m_control != nullptr) {
        m_control->getVariable(name, value);
    }
}

void GfComAsm::setVariable(const char* name, int value) {
    if (m_control != nullptr) {
        m_control->setVariable(name, value);
    }
}

void GfComAsm::changeLayer(unsigned int from, unsigned int to) {
    if (from == to) {
        return;
    }
    if (fw::AnimationManager* manager = mm::mtl::PtrSingleton<fw::AnimationManager>::get()) {
        if (m_sampler.isBind()) {
            manager->removePoseSampler(getLayer(), m_sampler);
            manager->addPoseSampler(to, m_sampler);
        }
        if (m_updater.isBind()) {
            manager->removeControlUpdater(getLayer(), m_updater);
            manager->addControlUpdater(to, m_updater);
        }
    }
}

mm::mtl::RTTI GfComAsm::m_rtti("GfComAsm", &GfComAnimation::m_rtti, nullptr);

}  // namespace gf
