#include "gf/SoundHandle.h"
#include "classes/gf/WeatherObj.h"
#include "classes/gf/WeatherEff.h"
#include "classes/gf/WeatherSnd.h"
#include "classes/gf/GfFieldWeather.h"
#include "classes/gf/GfGameManager.h"
#include "classes/fw/EffectManager.h"
#include "classes/gf/GfSound.h"
#include "classes/gf/GfFieldTime.h"
#include "classes/gf/GfPause.h"
#include "gf/GfDataMap.h"
#include "gf/SoundParam.h"
#include "gf/WeatherInfo.h"
#include <string.h>
#include "fw/UpdateInfo.h"

namespace gf {

bool WeatherEff::isPlay() const {
    return m_handle != 0;
}

void WeatherEff::destroy() {
    if (m_handle != 0) {
        fw::EffectManager::get()->remove(m_handle);
        m_handle = 0;
    }
}

void WeatherEff::fadeout(float) {
    if (m_handle != 0) {
        if (GfGameManager::isFadeout()) {
            fw::EffectManager::get()->remove(m_handle);
        } else {
            fw::EffectManager::get()->dead(m_handle);
        }
        m_handle = 0;
    }
}

// 1.0.0's; 3.0.1 keeps no copy (every use inlines it)
inline bool WeatherEff::isEraseEffect() const {
    if (m_isWait) {
        return false;
    }
    if (m_type == 0) {
        return false;
    }
    if (GfGameManager::isRoom()) {
        return true;
    }
    return !GfFieldWeather::isDispWeather();
}

// 1.0.0's; 3.0.1 keeps no copy (every use inlines it)
inline bool WeatherEff::isDispEffect() const {
    if (!m_isWait || m_type == 0) {
        return false;
    }
    if (GfGameManager::isRoom()) {
        return false;
    }
    return GfFieldWeather::isDispWeather();
}

void WeatherEff::update(const WeatherUpdateInfo& info, float) {
    if (m_handle != 0) {
        if (isEraseEffect()) {
            m_isWait = true;
            m_alpha = 1.0f;
        } else if (!fw::EffectManager::get()->isExist(m_handle)) {
            m_handle = 0;
        }
    }
    if (isDispEffect()) {
        m_isWait = false;
        create(m_type);
    }
    if (m_isWait && m_alpha > 0.0f) {
        m_alpha += info.m_deltaTime * -4.0f;
        if (m_alpha < 0.0f) {
            m_alpha = 0.0f;
            destroy();
        }
        applyAlpha(info);
    }
    applySpeed(info);
}

// 1.0.0's; 3.0.1 keeps no copy (every use inlines it)
inline void WeatherEff::applyAlpha(const WeatherUpdateInfo&) {
    if (m_handle != 0) {
        fw::EffectManager::get()->setAlpha(m_handle, m_alpha);
    }
}

// 1.0.0's; 3.0.1 keeps no copy (every use inlines it)
inline void WeatherEff::applySpeed(const WeatherUpdateInfo& info) {
    if (m_handle != 0) {
        fw::EffectManager::get()->setSpeed(m_handle, info.m_speed);
    }
}

void WeatherEff::setForceName(const char*) {}

void WeatherEff::setPause(bool) {}

bool WeatherSnd::isPlay() const {
    return m_handle.isValid();
}

void WeatherSnd::create(WEATYPE type) {
    GfSound* sound = GfSound::get();
    if (sound == nullptr) {
        return;
    }
    if (m_type != type) {
        m_isNoSound = false;
    }
    m_type = type;
    if (type == 0 || m_isNoSound) {
        return;
    }
    if (!GfFieldWeather::isDispWeather() || GfGameManager::isFadeout()) {
        return;
    }
    const char* name = GfDataMap::getWeatherSndName(type);
    if (name == nullptr) {
        return;
    }
    if (name[0] == '\0') {
        m_isNoSound = true;
        return;
    }
    SoundParam param;
    param.setName(name);
    param.m_kind = 8;
    m_handle = sound->playSe(param);
    if (!m_handle.isValid()) {
        m_isNoSound = true;
    }
    const char* beginName = GfDataMap::getWeatherSndBeginName(type);
    if (beginName == nullptr || beginName[0] == '\0') {
        return;
    }
    SoundParam beginParam;
    beginParam.setName(beginName);
    beginParam.m_kind = 8;
    sound->playSe(beginParam);
}

void WeatherSnd::destroy() {
    if (m_handle.isValid()) {
        if (GfSound::get() != nullptr) {
            GfSound::get()->stopSe(m_handle, 4.0f);
        }
        m_handle.clear();
    }
}

void WeatherSnd::fadeout(float time) {
    GfSound* sound = GfSound::get();
    if (sound != nullptr && m_handle.isValid()) {
        sound->stopSe(m_handle, time);
        m_handle.clear();
    }
}

void WeatherSnd::update(const WeatherUpdateInfo& info, float volume) {
    GfSound* sound = GfSound::get();
    if (sound == nullptr) {
        return;
    }
    float speed = -0.5f;
    if (!isRoomSe() && !isEraseSe()) {
        speed = 1.0f;
    }
    if (GfGameManager::isLeaveGameForDebug()) {
        speed = -1.0f;
    }
    m_volume += info.m_deltaTime * speed;
    float min = isRoomSe() ? 0.5f : 0.0f;
    if (isEraseSe()) {
        min = 0.0f;
    }
    if (m_volume < min) {
        m_volume = min;
    } else if (m_volume > 1.0f) {
        m_volume = 1.0f;
    }
    if (m_handle.isValid() && !sound->isPlaying(m_handle)) {
        m_handle.clear();
    }
    if (isCreateSe(volume)) {
        if (!info.m_isFadeout) {
            create(m_type);
        }
    } else if (m_volume * volume <= 0.0f) {
        m_volume = 0.0f;
        destroy();
    }
    applyVolume(info, volume);
}

// 1.0.0's; 3.0.1 keeps no copy (every use inlines it)
inline bool WeatherSnd::isRoomSe() const {
    return GfGameManager::isRoom();
}

// 1.0.0's; 3.0.1 keeps no copy (every use inlines it)
inline bool WeatherSnd::isEraseSe() const {
    if (!GfFieldWeather::isDispWeather() || GfGameManager::isStartGame()) {
        return true;
    }
    return GfGameManager::isLeaveGameForDebug();
}

// 1.0.0's; 3.0.1 keeps no copy (every use inlines it)
inline bool WeatherSnd::isCreateSe(float volume) const {
    if (m_handle.isValid()) {
        return false;
    }
    if (m_volume * volume > 0.0f && GfFieldWeather::isDispWeather() && !GfGameManager::isStartGame()) {
        return !GfGameManager::isLeaveGameForDebug();
    }
    return false;
}

// 1.0.0's; 3.0.1 keeps no copy (every use inlines it)
inline void WeatherSnd::applyVolume(const WeatherUpdateInfo&, float volume) {
    if (m_handle.isValid() && GfSound::get() != nullptr) {
        GfSound::get()->setVolume(m_handle, m_volume * volume, 0.0f);
    }
}

void WeatherSnd::setPause(bool) {}

WeatherInfo::~WeatherInfo() {
    destroyEnv();
    if (m_eff != nullptr) {
        delete m_eff;
        m_eff = nullptr;
    }
    if (m_snd != nullptr) {
        delete m_snd;
        m_snd = nullptr;
    }
}

// 1.0.0's; 3.0.1 keeps no copy (every use inlines it)
inline void WeatherInfo::destroyEnv() {
    m_eff->destroy();
    m_snd->destroy();
}

bool WeatherInfo::isTimeRangeOK() const {
    if (m_id >= 1 && m_id <= 4) {
        unsigned int bits = GfDataMap::getWeatherTimeBonus(m_mapId, m_id);
        if (GfFieldTime::get() != nullptr) {
            return (GfFieldTime::get()->getTimeRangeBits() & bits) != 0;
        }
    }
    return true;
}

bool WeatherInfo::isTimeup() const {
    return m_time == m_timeMax;
}

void WeatherInfo::fadeoutEnv(float time) {
    m_eff->fadeout(time);
    m_snd->fadeout(time);
    m_fadeTime = time;
    m_fadeTimeMax = time;
}

void WeatherInfo::update(const WeatherUpdateInfo& info) {
    m_eff->update(info, m_alpha);
    m_snd->update(info, m_alpha);
    if (!GfPause::isPause(0x10) && m_time < m_timeMax) {
        if (!info.m_isTimeStop) {
            m_time += info.m_deltaTime;
        }
        if (m_time > m_timeMax) {
            m_time = m_timeMax;
        }
    }
}

bool WeatherInfo::updateFadein(const fw::UpdateInfo& info) {
    if (info.m_deltaTime > 0.0f && m_fadeTime == 0.0f) {
        createEnv();
    }
    if (m_fadeTime >= m_fadeTimeMax) {
        return true;
    }
    m_fadeTime += info.m_deltaTime;
    if (m_fadeTime >= m_fadeTimeMax) {
        m_fadeTime = m_fadeTimeMax;
        m_alpha = 1.0f;
        return true;
    }
    m_alpha = m_fadeTime / m_fadeTimeMax;
    WeatherUpdateInfo updateInfo(info);
    update(updateInfo);
    return false;
}

// 1.0.0's; 3.0.1 keeps no copy (every use inlines it)
inline void WeatherInfo::createEnv() {
    m_eff->create(m_type);
    m_snd->create(m_type);
}

bool WeatherInfo::updateFadeout(const fw::UpdateInfo& info) {
    if (m_fadeTime <= 0.0f) {
        return true;
    }
    m_fadeTime -= info.m_deltaTime;
    if (m_fadeTime <= 0.0f) {
        m_alpha = 0.0f;
        m_fadeTime = 0.0f;
        return true;
    }
    m_alpha = m_fadeTime / m_fadeTimeMax;
    WeatherUpdateInfo updateInfo(info);
    updateInfo.m_isFadeout = true;
    update(updateInfo);
    return false;
}

bool WeatherInfo::isTimeEnd() const {
    return m_timeMax > 0.0f && m_time >= m_timeMax;
}

// 1.0.0's; 3.0.1 keeps no copy (every use inlines it)
inline bool WeatherInfo::isPlaySE() const {
    return m_snd->isPlay();
}

void WeatherInfo::setForceEffect(const char* name) {
    m_eff->setForceName(name);
    m_snd->setForceName(name);
}

void WeatherInfo::resetParam(float time, float timeMax, float fadeTime) {
    m_time = time;
    m_timeMax = timeMax;
    m_fadeTimeMax = fadeTime;
    m_fadeTime = fadeTime;
    m_alpha = m_fadeTimeMax > 0.0f ? m_fadeTime / m_fadeTimeMax : 1.0f;
}

void WeatherInfo::setPause(bool pause) {
    m_eff->setPause(pause);
    m_snd->setPause(pause);
}

WeatherUpdateInfo::WeatherUpdateInfo(const fw::UpdateInfo& info)
    : m_speed(info.m_speed), m_deltaTime(info.m_deltaTime), m_isFadeout(false), m_isTimeStop(false) {}

}  // namespace gf
