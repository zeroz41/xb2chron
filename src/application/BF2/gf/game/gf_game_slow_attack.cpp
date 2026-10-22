#include "math.h"
#include "classes/gf/GfSlowAttack.h"
#include "classes/gf/GfGameSpeed.h"
#include "classes/gf/GfSound.h"
#include "classes/gf/GfAllocator.h"

namespace gf {

GfSlowAttack::~GfSlowAttack() {}

void GfSlowAttack::updateForIdle(const fw::UpdateInfo& info) {
    if (m_execute) {
        m_state = 1;
        m_update.set(this, &GfSlowAttack::updateForPlay);
    }
}

void GfSlowAttack::updateForPlay(const fw::UpdateInfo& info) {
    float speed = GfGameSpeed::getPlaySpeed();
    if (GfSound* sound = GfSound::get()) {
        speed = fmaxf(speed, 0.001f);
        sound->setCategoryPitch(fw::SoundCategory(5), speed, 0.0f);
        sound->setCategoryPitch(fw::SoundCategory(6), speed, 0.0f);
        sound->setCategoryPitch(fw::SoundCategory(7), speed, 0.0f);
        sound->setCategoryPitch(fw::SoundCategory(8), speed, 0.0f);
        sound->setCategoryPitch(fw::SoundCategory(13), speed, 0.0f);
    }
    if (!m_execute) {
        m_state = 2;
        m_update.set(this, &GfSlowAttack::updateForTerm);
    }
}

void GfSlowAttack::updateForTerm(const fw::UpdateInfo& info) {
    if (GfSound* sound = GfSound::get()) {
        sound->setCategoryPitch(fw::SoundCategory(5), 1.0f, 0.0f);
        sound->setCategoryPitch(fw::SoundCategory(6), 1.0f, 0.0f);
        sound->setCategoryPitch(fw::SoundCategory(7), 1.0f, 0.0f);
        sound->setCategoryPitch(fw::SoundCategory(8), 1.0f, 0.0f);
        sound->setCategoryPitch(fw::SoundCategory(13), 1.0f, 0.0f);
    }
    m_update.set(this, &GfSlowAttack::updateForIdle);
    m_state = 0;
}

void GfSlowAttack::update(const fw::UpdateInfo& info) {
    if (m_update.isValid()) {
        m_update(info);
    }
    if (m_execute) {
        m_execute = false;
    }
}

GfSlowAttack* GfSlowAttack::create() {
    GfSlowAttack* slow = get();
    if (slow == nullptr) {
#line 109
        slow = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfSlowAttack();
    }
    return slow;
}

void GfSlowAttack::destroy() {
    GfSlowAttack* slow = get();
    if (slow != nullptr) {
        slow->m_update.set(slow, &GfSlowAttack::updateForIdle);
        slow->m_state = 0;
        delete slow;
    }
}

void GfSlowAttack::executeSlow() {
    m_execute = true;
}

}  // namespace gf
