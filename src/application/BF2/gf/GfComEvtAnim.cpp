#include "classes/fw/AnimPoseSamper.h"
#include "classes/fw/AnimBlenderUpdater.h"
#include "classes/fw/AnimEventAsmPoseSampler.h"
#include "classes/fw/AnimEventMotPoseSamper.h"
#include "classes/gf/GfComEvtAnim.h"
#include "classes/gf/GfComEvtAnim/Asm.h"
#include "classes/gf/GfComEvtAnim/Asm/AsmLisener.h"
#include "classes/gf/GfComEvtAnim/Asm/ViewerListener.h"
#include "anm/Util.h"
#include "anm/Factory.h"
#include "anm/AnimationImporter.h"
#include "anm/StateMachine.h"
#include "classes/anm/ResASM.h"
#include "classes/anm/ASMControl.h"
#include "classes/anm/Binding.h"
#include "classes/anm/Blender.h"
#include "classes/anm/Control.h"
#include "classes/fw/AnimationManager.h"
#include "fw/Message.h"
#include "classes/fw/UpdatableObject.h"
#include "classes/gf/GfComModel.h"
#include "classes/gf/GfObj.h"
#include "gf/GfObjAcc.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/Quat.h"
#include "mm/Vec3.h"
#include "mm/Vec4.h"
#include "anm/QsTransform.h"
#include <string.h>

namespace gf {

bool GfComEvtAnim::recieveMessage(fw::MessageObject*, fw::Message& msg) {
    return msg.m_id == 0x1000003;
}

void GfComEvtAnim::Asm::cleanup(unsigned int layer) {
    if (m_control == nullptr) {
        return;
    }
    if (m_flags & 1) {
        if (fw::AnimationManager* manager = mm::mtl::PtrSingleton<fw::AnimationManager>::get()) {
            manager->removePoseSampler(layer, m_sampler);
            manager->removeControlUpdater(layer, m_updater);
        }
        m_flags &= ~1;
    }
    m_sampler.unbind();
    m_updater.unbind();
    m_caches.clear();
    m_control->setListener(nullptr);
    if (m_control != nullptr) {
        m_control->release();
        m_control = nullptr;
    }
}

void GfComEvtAnim::Asm::setup(unsigned int layer, GfComModel* model, anm::ResASM* res, const char* state,
                              bool sampleFlag) {
    m_model = model;
    if (res == nullptr) {
        return;
    }
    anm::Pose* pose = model->m_pose;
    if (pose == nullptr) {
        return;
    }
    anm::ExtraTruckBuffer* extra = model->m_extraTruckBuffer;
    m_control = anm::Factory::createASMControl(*res, *getAllocator(ALLOCATOR(7)));
    m_updater.bind(m_control);
    if (!m_updater.isBind()) {
        return;
    }
    m_sampler.m_sampleFlag = sampleFlag;
    m_sampler.bind(m_control, pose, extra);
    if (!m_sampler.isBind()) {
        return;
    }
    if (fw::AnimationManager* manager = mm::mtl::PtrSingleton<fw::AnimationManager>::get()) {
        manager->addControlUpdater(layer, m_updater);
        manager->addPoseSampler(layer, m_sampler);
        m_flags |= 1;
    }
    m_control->setListener(&m_asmListener);
    m_caches.reserve(32, 8);
    m_control->m_stateMachines[0].setState(state, anm::StartFrameType(0));
    m_control->m_stateMachines[0].executeCmd("C_idle");
}

void GfComEvtAnim::Asm::executeCallback(GfComEvtAnim* owner) {
    for (unsigned int i = 0; i < m_caches.size(); ++i) {
        const anm::AsmAnnotetion* event = m_caches[i].m_event;
        bool handled = false;
        for (int j = 1; j < 5; ++j) {
            if (m_callbacks[j].delegate.isValid() && strcmp(m_callbacks[j].name, event->m_name) == 0) {
                m_callbacks[j].delegate(owner, m_caches[i]);
                handled = true;
                break;
            }
        }
        if (!handled && m_callbacks[0].delegate.isValid()) {
            m_callbacks[0].delegate(owner, m_caches[i]);
        }
    }
    m_caches.clear();
}

void GfComEvtAnim::Mot::stop(unsigned int layer) {
    if (m_blender == nullptr) {
        return;
    }
    if (m_flags & 1) {
        if (fw::AnimationManager* manager = mm::mtl::PtrSingleton<fw::AnimationManager>::get()) {
            m_sampler.resetPose();
            manager->removePoseSampler(layer, m_sampler);
            manager->removeControlUpdater(layer, m_updater);
        }
        m_flags &= ~1;
    }
    for (unsigned long i = 0; i < m_count; ++i) {
        m_blender->removeControl(m_controls[i]);
        if (m_controls[i] != nullptr) {
            m_controls[i]->release();
            m_controls[i] = nullptr;
        }
    }
    m_count = 0;
    m_current = 0;
    m_speed = 1.0f;
}

void GfComEvtAnim::Mot::init(unsigned int layer, void** data, unsigned long*, unsigned long count) {
    if (count == 0 || m_blender == nullptr) {
        return;
    }
    stop(layer);
    for (unsigned long i = 0; i < count; ++i) {
        anm::Binding* binding = anm::AnimationImporter::import(data[i]);
        m_controls[i] = anm::Factory::createControl(binding, getAllocator(ALLOCATOR(7)));
        m_playbackTimes[i] = anm::Util::getPlayBackTime(*binding);
        m_blender->addControl(m_controls[i]);
        if (binding != nullptr) {
            binding->release();
        }
    }
    if (fw::AnimationManager* manager = mm::mtl::PtrSingleton<fw::AnimationManager>::get()) {
        manager->addControlUpdater(layer, m_updater);
        manager->addPoseSampler(layer, m_sampler);
        m_flags |= 1;
    }
    for (unsigned long i = 0; i < count; ++i) {
        anm::Control* control = m_controls[i];
        control->m_speed = 0.0f;
        control->m_weight = i == 0 ? 1.0f : 0.0f;
    }
    m_current = 0;
    m_count = count;
    m_speed = 1.0f;
}

bool GfComEvtAnim::Mot::easeIn(const char* name, AnimLayer) {
    if (m_blender == nullptr) {
        return false;
    }
    if (m_res == nullptr) {
        GfObjAcc acc(static_cast<GfObj*>(m_model->m_owner)->m_handle);
        return false;
    }
    for (const mm::mtl::FixStr<32>& easeName : m_easeNames) {
        if (strcmp(easeName.m_str, name) == 0) {
            return false;
        }
    }
    const anm::Binding* binding = anm::Util::getAsmBinding(*m_res, name, 0);
    if (binding == nullptr) {
        return false;
    }
    anm::Control* control = anm::Factory::createControl(binding, getAllocator(ALLOCATOR(7)));
    m_blender->addControl(control);
    control->m_weight = 1.0f;
    control->m_speed = 1.0f;
    m_easeNames.push_back(mm::mtl::FixStr<32>(name));
    m_easeControls.push_back(control);
    return true;
}

bool GfComEvtAnim::Mot::easeOut(const char* name, AnimLayer) {
    if (m_blender == nullptr) {
        return false;
    }
    anm::Control** it = m_easeControls.begin();
    for (mm::mtl::FixStr<32>* easeName = m_easeNames.begin(); it != m_easeControls.end(); ++it, ++easeName) {
        if (strcmp(easeName->m_str, name) == 0) {
            m_blender->removeControl(*it);
            if (*it != nullptr) {
                (*it)->release();
                *it = nullptr;
            }
            m_easeControls.erase(it);
            m_easeNames.erase(easeName);
            return true;
        }
    }
    return false;
}

GfComEvtAnim::GfComEvtAnim() : m_res(nullptr), m_setupFlags(0), m_sampleFlag(true) {}

void GfComEvtAnim::cleanup() {
    m_mot.cleanup(getLayer());
    m_asm.cleanup(getLayer());
    m_res = nullptr;
    m_state = "";
    m_setupFlags = 0;
}

void GfComEvtAnim::setup(const SetupInfo& info) {
    m_res = info.m_res;
    m_state = info.m_state;
    m_sampleFlag = info.m_sampleFlag;
    updateSetup();
}

// inline: updateSetup inlines it (the name is not the original's)
inline void GfComEvtAnim::Mot::setup(GfComModel* model, anm::ResASM* res, bool sampleFlag) {
    m_model = model;
    m_res = res;
    if (anm::Pose* pose = model->m_pose) {
        anm::ExtraTruckBuffer* extra = model->m_extraTruckBuffer;
        m_blender = anm::Factory::createBlender(model->m_skeleton, getAllocator(ALLOCATOR(7)));
        m_updater.bind(m_blender);
        if (m_updater.m_blender != nullptr) {
            m_sampler.m_sampleFlag = sampleFlag;
            m_sampler.bind(m_blender, pose, extra);
        }
    }
}

void GfComEvtAnim::updateSetup() {
    if (m_setupFlags & 1) {
        return;
    }
    if (GfComModel* model = m_owner->getComponent<GfComModel>(1)) {
        m_asm.setup(getLayer(), model, m_res, m_state.m_str, m_sampleFlag);
        m_mot.setup(model, m_res, m_sampleFlag);
        m_setupFlags |= 1;
    }
}

void GfComEvtAnim::changeLayer(unsigned int oldLayer, unsigned int newLayer) {
    if (oldLayer == newLayer) {
        return;
    }
    if (m_asm.m_control != nullptr && (m_asm.m_flags & 1)) {
        if (fw::AnimationManager* manager = mm::mtl::PtrSingleton<fw::AnimationManager>::get()) {
            if (m_asm.m_sampler.isBind()) {
                manager->removePoseSampler(oldLayer, m_asm.m_sampler);
                manager->addPoseSampler(newLayer, m_asm.m_sampler);
            }
            if (m_asm.m_updater.isBind()) {
                manager->removeControlUpdater(oldLayer, m_asm.m_updater);
                manager->addControlUpdater(newLayer, m_asm.m_updater);
            }
        }
    }
    if (m_mot.m_blender != nullptr && (m_mot.m_flags & 1)) {
        if (fw::AnimationManager* manager = mm::mtl::PtrSingleton<fw::AnimationManager>::get()) {
            if (m_mot.m_sampler.isBind()) {
                manager->removePoseSampler(oldLayer, m_mot.m_sampler);
                manager->addPoseSampler(newLayer, m_mot.m_sampler);
            }
            if (m_mot.m_updater.m_blender != nullptr) {
                manager->removeControlUpdater(oldLayer, m_mot.m_updater);
                manager->addControlUpdater(newLayer, m_mot.m_updater);
            }
        }
    }
}

bool GfComEvtAnim::execCmd(const char* cmd) {
    if (m_asm.m_control != nullptr) {
        return m_asm.m_control->m_stateMachines[0].executeCmd(cmd);
    }
    return false;
}

const char* GfComEvtAnim::getStateName() const {
    if (m_asm.m_control != nullptr) {
        return m_asm.m_control->m_stateMachines[0].getStateName();
    }
    return nullptr;
}

bool GfComEvtAnim::setState(const char* state) {
    if (m_asm.m_control != nullptr) {
        return m_asm.m_control->m_stateMachines[0].setState(state, anm::StartFrameType(0));
    }
    return false;
}

void GfComEvtAnim::setVariable(const char* name, float value) {
    if (m_asm.m_control != nullptr) {
        m_asm.m_control->setVariable(name, value);
    }
}

void GfComEvtAnim::setVariable(const char* name, int value) {
    if (m_asm.m_control != nullptr) {
        m_asm.m_control->setVariable(name, value);
    }
}

void GfComEvtAnim::setLocalTime(float time, AnimLayer layer) {
    if (layer <= 6 && m_asm.m_control != nullptr) {
        m_asm.m_control->m_stateMachines[layer].setLocalTime(time);
    }
}

bool GfComEvtAnim::getPlaybackTime(const char* state, float* pTime) const {
    if (m_asm.m_control != nullptr) {
        if (const anm::ResASM* res = m_asm.m_control->m_pRes) {
            return anm::Util::getAsmPlaybackTime(*res, state, 0, pTime);
        }
    }
    return false;
}

bool GfComEvtAnim::getLocomotionReference(const char* state, float time, anm::QsTransform* pOut) const {
    if (m_asm.m_control != nullptr) {
        if (const anm::ResASM* res = m_asm.m_control->m_pRes) {
            return anm::Util::getAsmLocomotionReference(*res, state, time, 0, pOut);
        }
    }
    return false;
}

const anm::QsTransform* GfComEvtAnim::getLocomotion() const {
    if (m_asm.m_control != nullptr) {
        return &m_asm.m_control->m_locomotion;
    }
    // set on every call: the guard only covers its (empty) constructor
    static anm::QsTransform s_identity;
    s_identity.m_translation = mm::Vec4::zero;
    s_identity.m_rotation = mm::Quat::identity;
    s_identity.m_scale = mm::Vec4::unit;
    return &s_identity;
}

bool GfComEvtAnim::isEnd(AnimLayer layer) const {
    if (m_asm.m_control == nullptr) {
        return true;
    }
    if (layer <= 6) {
        return m_asm.m_control->m_stateMachines[layer].isEnd();
    }
    return false;
}

void GfComEvtAnim::play(void* data, unsigned long size, float time) {
    updateSetup();
    m_mot.init(getLayer(), &data, &size, 1);
    m_mot.play(0, time);
    m_asm.setPause(getLayer(), true);
    m_asm.updateViewer(getLayer());
}

void GfComEvtAnim::stop() {
    m_mot.stop(getLayer());
    m_asm.setPause(getLayer(), false);
    m_asm.updateViewer(getLayer());
}

void GfComEvtAnim::initMulti(void** data, unsigned long* sizes, unsigned long count) {
    updateSetup();
    m_mot.init(getLayer(), data, sizes, count);
}

void GfComEvtAnim::playMulti(unsigned int index, float time) {
    m_mot.play(index, time);
    m_asm.setPause(getLayer(), true);
    m_asm.updateViewer(getLayer());
}

void GfComEvtAnim::stopMulti() {
    m_mot.stop(getLayer());
    m_asm.setPause(getLayer(), false);
    m_asm.updateViewer(getLayer());
}

bool GfComEvtAnim::isEndMulti() const {
    return m_mot.isEnd();
}

void GfComEvtAnim::setWeightMulti(float* weights, unsigned long count) {
    if (m_mot.m_blender == nullptr) {
        return;
    }
    for (unsigned long i = 0; i < count; ++i) {
        if (i >= m_mot.m_count) {
            break;
        }
        anm::Control* control = m_mot.m_controls[i];
        control->m_weight = weights[i];
    }
}

void GfComEvtAnim::setSpeed(float speed, AnimLayer layer) {
    updateSetup();
    if (layer <= 6 && m_asm.m_control != nullptr) {
        m_asm.m_control->m_stateMachines[layer].setSpeed(speed);
    }
    for (unsigned long i = 0; i < m_mot.m_count; ++i) {
        anm::Control* control = m_mot.m_controls[i];
        control->m_speed = i == m_mot.m_current ? speed : 0.0f;
    }
    m_mot.m_speed = speed;
}

mm::mtl::RTTI GfComEvtAnim::m_rtti("GfComEvtAnim", &GfComAnimation::m_rtti, nullptr);

}  // namespace gf
