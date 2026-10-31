#include "mm/mtl/FixStr.h"
#include "mm/mtl/FixedQueue.h"
#include "classes/gf/BgmTrack.h"
#include "classes/gf/BgmEvent.h"
#include "classes/gf/GfGameScene.h"
#include "classes/gf/GfEvtBgm.h"
#include "classes/gf/EvtBgmTask.h"
#include "classes/gf/EvtBgmTaskDelay.h"
#include "classes/gf/EvtBgmTaskDelayStop.h"
#include "classes/gf/EvtBgmTaskVolume.h"
#include "classes/gf/GfAllocator.h"
#include "fw/UpdateInfo.h"
#include "mm/Math.h"

namespace gf {

GfEvtBgm::~GfEvtBgm() {}

void GfEvtBgm::clear() {
    for (mm::mtl::FixedQueue<EvtBgmTask*, 128>::iterator it = m_tasks.begin(), end = m_tasks.end(); it != end; ++it) {
        if (*it != nullptr) {
            delete *it;
        }
    }
    m_tasks.clear();
    m_currentTask = nullptr;
    m_setup.m_name.clear();
    if (BgmEvent* event = BgmEvent::get()) {
        event->stopBGM(1.0f);
    }
}

void GfEvtBgm::build(const GfSetupParam& param) {
#line 70
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfEvtBgm(param);
}

void GfEvtBgm::destroy() {
    GfEvtBgm* bgm = get();
    bgm->finalize();
    delete bgm;
}

void GfEvtBgm::playBgm(const EventBgmSetup& setup) {
    if (isPlayBgm()) {
        if (m_setup.m_stopTime > 0.0f) {
            m_tasks.push_back(EvtBgmTaskDelayStop::create(m_setup));
        }
    }
    while (!m_tasks.empty() && m_tasks.back()->isVolumeTask()) {
        if (m_tasks.back() != nullptr) {
            delete m_tasks.back();
            m_tasks.back() = nullptr;
        }
        m_tasks.pop_back();
    }
    m_tasks.push_back(EvtBgmTaskDelay::create(setup));
}

bool GfEvtBgm::isPlayBgm() const {
    if (BgmEvent::get()->isPlaying() || m_state != PLAY_STATE_STOP) {
        return true;
    }
    for (mm::mtl::FixedQueue<EvtBgmTask*, 128>::const_iterator it = m_tasks.begin(), end = m_tasks.end(); it != end;
         ++it) {
        if ((*it)->isPlayTask()) {
            return true;
        }
    }
    return false;
}

inline EvtBgmTaskDelay* EvtBgmTaskDelay::create(const EventBgmSetup& setup) {
#line 355
    return new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) EvtBgmTaskDelay(setup);
}

inline EvtBgmTaskDelayStop* EvtBgmTaskDelayStop::create(const EventBgmSetup& setup) {
#line 400
    return new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) EvtBgmTaskDelayStop(setup);
}

void GfEvtBgm::stopBgm(const EventBgmSetup& setup) {
    if (m_setup.m_overTime != 0.0f) {
        if (BgmEvent* event = BgmEvent::get()) {
            event->fn_7100265440();
        }
        return;
    }
    m_tasks.push_back(EvtBgmTaskDelayStop::create(setup));
}

void GfEvtBgm::cancelOverTime() {
    m_setup.m_overTime = 0.0f;
    if (BgmEvent* event = BgmEvent::get()) {
        event->cancelOverTime();
    }
}

inline EvtBgmTaskVolume* EvtBgmTaskVolume::create(const EventBgmSetup& setup) {
#line 445
    return new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) EvtBgmTaskVolume(setup);
}

void GfEvtBgm::changeBgmVolume(const EventBgmSetup& setup) {
    m_tasks.push_back(EvtBgmTaskVolume::create(setup));
}

void GfEvtBgm::setFadeoutVolume() {
    if (m_state == PLAY_STATE_PLAY && m_tasks.size() == 0) {
        m_state = PLAY_STATE_STOP;
    }
}

bool GfEvtBgm::isEnableEventBgm() const {
    return m_state == PLAY_STATE_NO_BGM || m_state == PLAY_STATE_PLAY || m_state == PLAY_STATE_STOP_DELAY;
}

void GfEvtBgm::setPlayBgmTakeOver(const char* name) {
    m_setup.m_name = name;
}

float GfEvtBgm::getPlayBgmTime() const {
    if (BgmEvent* event = BgmEvent::get()) {
        return event->getPlayTime();
    }
    return 0.0f;
}

float GfEvtBgm::getTotalBgmTime() const {
    if (BgmEvent* event = BgmEvent::get()) {
        return event->getTotalTime();
    }
    return 0.0f;
}

void GfEvtBgm::updateBgmTask(const fw::UpdateInfo& info) {
    if (m_tasks.size() == 0) {
        return;
    }
    if (m_currentTask == nullptr) {
        m_currentTask = m_tasks.front();
        m_currentTask->start(this);
    }
    if (m_currentTask->update(this, info)) {
        if (m_currentTask != nullptr) {
            delete m_currentTask;
            m_currentTask = nullptr;
        }
        m_tasks.pop();
    }
}

void GfEvtBgm::update(const fw::UpdateInfo& info) {
    updateBgmTask(info);
}

void EvtBgmTaskDelay::start(GfEvtBgm* bgm) {
    if (bgm->m_setup.m_noBgm) {
        bgm->setPlayState(GfEvtBgm::PLAY_STATE_NO_BGM);
        bgm->m_setup.m_name = "";
    } else {
        bgm->setPlayState(GfEvtBgm::PLAY_STATE_DELAY);
    }
}

bool EvtBgmTaskDelay::update(GfEvtBgm* bgm, const fw::UpdateInfo& info) {
    if (!m_cancel) {
        m_setup.m_delay -= info.m_deltaTime;
        if (m_setup.m_delay > 0.0f) {
            return false;
        }
        bgm->setPlayState(GfEvtBgm::PLAY_STATE_PLAY);
        bgm->setPlayParam(m_setup);
        if (m_setup.m_stopTime > 0.0f) {
            if (GfGameScene* scene = GfGameScene::get()) {
                scene->setForceEventBgm(m_setup.m_stopTime);
            }
        }
    }
    return true;
}

void EvtBgmTaskDelay::cancel(GfEvtBgm* bgm) {
    m_cancel = true;
}

void EvtBgmTaskDelayStop::start(GfEvtBgm* bgm) {
    bgm->setPlayState(GfEvtBgm::PLAY_STATE_STOP_DELAY);
}

bool EvtBgmTaskDelayStop::update(GfEvtBgm* bgm, const fw::UpdateInfo& info) {
    if (!m_cancel) {
        m_time -= info.m_deltaTime;
        if (m_time > 0.0f) {
            return false;
        }
        bgm->setPlayParam(m_setup);
        bgm->setPlayState(GfEvtBgm::PLAY_STATE_STOP);
        if (GfGameScene* scene = GfGameScene::get()) {
            scene->setForceEventBgm(0.0f);
        }
    }
    return true;
}

void EvtBgmTaskDelayStop::cancel(GfEvtBgm* bgm) {
    m_cancel = true;
}

void EvtBgmTaskVolume::start(GfEvtBgm* bgm) {}

bool EvtBgmTaskVolume::update(GfEvtBgm* bgm, const fw::UpdateInfo& info) {
    if (m_cancel) {
        return true;
    }
    if (info.m_deltaTime < 1e-6f) {
        return false;
    }
    float time = m_time - info.m_deltaTime;
    m_time = time <= 0.0f ? 0.0f : time;
    float diff = m_volume - bgm->m_setup.m_volume;
    if (mm::fabs(diff) <= 1e-6f) {
        return true;
    }
    float rate = m_time == 0.0f ? 1.0f : info.m_deltaTime / m_time;
    bgm->m_setup.m_volume = bgm->m_setup.m_volume + diff * rate;
    return m_time <= 0.0f;
}

void EvtBgmTaskVolume::cancel(GfEvtBgm* bgm) {
    m_cancel = true;
}

}  // namespace gf
