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
#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/Quat.h"
#include "mm/Vec3.h"
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

GfComEvtAnim::GfComEvtAnim() : m_res(nullptr), m_setupFlags(0), m_sampleFlag(true) {}

void GfComEvtAnim::setup(const SetupInfo& info) {
    m_res = info.m_res;
    m_state = info.m_state;
    m_sampleFlag = info.m_sampleFlag;
    updateSetup();
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

bool GfComEvtAnim::isEnd(AnimLayer layer) const {
    if (m_asm.m_control == nullptr) {
        return true;
    }
    if (layer <= 6) {
        return m_asm.m_control->m_stateMachines[layer].isEnd();
    }
    return false;
}

mm::mtl::RTTI GfComEvtAnim::m_rtti("GfComEvtAnim", &GfComAnimation::m_rtti, nullptr);

}  // namespace gf
