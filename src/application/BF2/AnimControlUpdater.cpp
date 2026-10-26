#include "classes/anm/Blender.h"
#include "classes/anm/ASMControl.h"
#include "classes/fw/AnimControlUpdater.h"
#include "classes/fw/AnimBlenderUpdater.h"
#include "classes/fw/AnimAsmUpdater.h"
#include "classes/anm/Control.h"
#include "classes/anm/Blender.h"
#include "classes/anm/ASMControl.h"
#include "fw/UpdateInfo.h"

namespace fw {

AnimControlUpdater::AnimControlUpdater() : m_control(nullptr) {}

AnimControlUpdater::~AnimControlUpdater() {
    unbind();
}

void AnimControlUpdater::unbind() {
    if (m_control != nullptr) {
        m_control->release();
        m_control = nullptr;
    }
}

void AnimControlUpdater::bind(anm::Control* control) {
    unbind();
    m_control = control;
    control->addRef();
}

void AnimControlUpdater::update(fw::UpdateInfo const& info) {
    m_control->update(info.m_deltaTime);
}

AnimBlenderUpdater::AnimBlenderUpdater() : m_blender(nullptr) {}

AnimBlenderUpdater::~AnimBlenderUpdater() {
    unbind();
}

void AnimBlenderUpdater::unbind() {
    if (m_blender != nullptr) {
        m_blender->release();
        m_blender = nullptr;
    }
}

void AnimBlenderUpdater::bind(anm::Blender* blender) {
    unbind();
    m_blender = blender;
    blender->addRef();
}

void AnimBlenderUpdater::update(fw::UpdateInfo const& info) {
    m_blender->update(info.m_deltaTime);
}

AnimAsmUpdater::AnimAsmUpdater() : m_control(nullptr) {}

AnimAsmUpdater::~AnimAsmUpdater() {
    unbind();
}

void AnimAsmUpdater::unbind() {
    if (m_control != nullptr) {
        m_control->release();
        m_control = nullptr;
    }
}

void AnimAsmUpdater::bind(anm::ASMControl* control) {
    unbind();
    m_control = control;
    control->addRef();
}

void AnimAsmUpdater::update(fw::UpdateInfo const& info) {
    m_control->updateFrame(info.m_deltaTime);
}

}  // namespace fw
