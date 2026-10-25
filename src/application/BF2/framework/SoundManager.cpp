#include "classes/fw/ISoundDriver.h"
#include "classes/fw/SoundSsdDriver.h"
#include "classes/fw/SoundManager.h"
#include "classes/fw/Framework.h"
#include "classes/fw/FrameworkMemory.h"
#include "fw/UpdateInfo.h"
#include "mm/Math.h"

namespace fw {
SoundManager::UniqueID SoundManager::m_uniqueID = {0, 1, 0xFFFFFFFF};

SoundManager::~SoundManager() {
    if (m_commonSe != nullptr) {
        m_commonSe->release();
        m_commonSe = nullptr;
    }
    if (m_battleElemSe != nullptr) {
        m_battleElemSe->release();
        m_battleElemSe = nullptr;
    }
    if (m_battleWeaponSe != nullptr) {
        m_battleWeaponSe->release();
        m_battleWeaponSe = nullptr;
    }
    if (m_battleSystemSe != nullptr) {
        m_battleSystemSe->release();
        m_battleSystemSe = nullptr;
    }
    if (m_driver != nullptr) {
        delete m_driver;
        m_driver = nullptr;
    }
}

void SoundManager::attachPoolMemory(void* memory, unsigned int size) {
    if (isDriverEnable()) {
        m_driver->attachPoolMemory(memory, size);
    }
}

void SoundManager::pauseAll(bool pause, float fade) {
    if (isDriverEnable()) {
        if (pause) {
            if (m_pauseCount == 0) {
                m_driver->pauseAll(true, fade);
            }
            ++m_pauseCount;
        } else if (m_pauseCount > 0) {
            if (--m_pauseCount == 0) {
                m_driver->pauseAll(false, fade);
            }
        }
    }
}

void SoundManager::tail(const UpdateInfo&) {
    if (isFinalized()) {
        return;
    }
}

mm::mtl::IAllocator* SoundManager::getProcAllocator() {
    return FrameworkMemory::getAllocator(7);
}

void SoundManager::setListeningPoint(const mm::Mat44& mtx) {
    if (m_driver != nullptr) {
        m_driver->setListeningPoint(mtx);
    }
}

void SoundManager::setCategoryVolume(SoundCategory category, float volume, float fade) {
    if (m_driver != nullptr) {
        m_driver->setCategoryVolume(category, volume, fade);
    }
}

void SoundManager::setCategoryPitch(SoundCategory category, float pitch, float fade) {
    if (m_driver != nullptr) {
        m_driver->setCategoryPitch(category, pitch, fade);
    }
}

unsigned int SoundManager::playBgm(const char* name, float volume, bool flag, int param, SoundCategory category) {
    if (!isDriverEnable()) {
        return 0;
    }
    unsigned int handle = m_driver->playBgm(name, volume, flag, param, category);
    if (handle != 0 && !flag && isDriverEnable() && m_pauseCount != 0) {
        m_driver->pause(handle, true, 0.0f);
    }
    return handle;
}

bool SoundManager::startBgm(unsigned int handle) {
    if (isDriverEnable() && handle != 0) {
        return m_driver->startBgm(handle);
    }
    return false;
}

void SoundManager::stopBgm(unsigned int handle, float fade) {
    if (isDriverEnable() && handle != 0) {
        m_driver->stopBgm(handle, fade);
    }
}

unsigned int SoundManager::playVoice(const char* name, float volume, bool flag, SoundCategory category) {
    if (!isDriverEnable()) {
        return 0;
    }
    unsigned int handle = m_driver->playVoice(name, volume, flag, category);
    if (handle != 0 && !flag && isDriverEnable() && m_pauseCount != 0) {
        m_driver->pause(handle, true, 0.0f);
    }
    return handle;
}

bool SoundManager::startVoice(unsigned int handle) {
    if (isDriverEnable() && handle != 0) {
        return m_driver->startVoice(handle);
    }
    return false;
}

void SoundManager::stopVoice(unsigned int handle, float fade) {
    if (isDriverEnable() && handle != 0) {
        m_driver->stopVoice(handle, fade);
    }
}

SoundPack* SoundManager::getCommonPack() {
    if (mm::mtl::PtrSingleton<Framework>::get() != nullptr && m_dlc) {
        return findPack("dlc_common", nullptr);
    }
    return findPack("common", nullptr);
}

void SoundManager::stopSe(unsigned int handle, float fade) {
    if (isDriverEnable() && handle != 0) {
        m_driver->stopSe(handle, fade);
    }
}

bool SoundManager::isValid(unsigned int handle) const {
    if (isDriverEnable() && handle != 0) {
        return m_driver->isValid(handle);
    }
    return false;
}

bool SoundManager::isPlaying(unsigned int handle) const {
    if (isDriverEnable() && handle != 0) {
        if (m_driver->isPreparing(handle) || m_driver->isReady(handle) || m_driver->isPlaying(handle)) {
            return true;
        }
        return m_driver->isPause(handle);
    }
    return false;
}

bool SoundManager::isPause(unsigned int handle) const {
    if (isDriverEnable() && handle != 0) {
        return m_driver->isPause(handle);
    }
    return false;
}

bool SoundManager::isPreparing(unsigned int handle) const {
    if (isDriverEnable() && handle != 0) {
        return m_driver->isPreparing(handle);
    }
    return false;
}

bool SoundManager::isPrepared(unsigned int handle) const {
    if (isDriverEnable() && handle != 0) {
        return m_driver->isReady(handle);
    }
    return false;
}

void SoundManager::setCategory(unsigned int handle, SoundCategory category) {
    if (isDriverEnable() && handle != 0) {
        m_driver->setCategory(handle, category);
    }
}

void SoundManager::setVolume(unsigned int handle, float volume, float fade) {
    if (isDriverEnable() && handle != 0) {
        m_driver->setVolume(handle, volume, fade);
    }
}

float SoundManager::getVolume(unsigned int handle, SoundVolumeType type) {
    if (isDriverEnable() && handle != 0) {
        return m_driver->getVolume(handle, type);
    }
    return 0.0f;
}

void SoundManager::setPitch(unsigned int handle, float pitch, float fade) {
    if (isDriverEnable() && handle != 0) {
        m_driver->setPitch(handle, pitch, fade);
    }
}

void SoundManager::setPan(unsigned int handle, float pan, float fade) {
    if (isDriverEnable() && handle != 0) {
        m_driver->setPan(handle, pan, fade);
    }
}

void SoundManager::setPos(unsigned int handle, const mm::Vec3& pos) {
    if (isDriverEnable() && handle != 0) {
        m_driver->setPos(handle, pos);
    }
}

bool SoundManager::setPlayTime(unsigned int handle, float time) {
    if (isDriverEnable() && handle != 0) {
        return m_driver->setPlayTime(handle, time);
    }
    return false;
}

bool SoundManager::getPlayTime(unsigned int handle, float& time) {
    if (isDriverEnable() && handle != 0) {
        return m_driver->getPlayTime(handle, time);
    }
    return false;
}

bool SoundManager::getTotalTime(unsigned int handle, float& time) {
    if (isDriverEnable() && handle != 0) {
        return m_driver->getTotalTime(handle, time);
    }
    return false;
}

bool SoundManager::isLoop(unsigned int handle) {
    if (isDriverEnable() && handle != 0) {
        return m_driver->isLoop(handle);
    }
    return false;
}

bool SoundManager::isLoop(unsigned int handle, SoundPack* pack) {
    if (isDriverEnable()) {
        if (pack == nullptr) {
            pack = getCommonPack();
        }
        return m_driver->isLoop(handle, pack);
    }
    return false;
}

void SoundManager::pause(unsigned int handle, bool pause, float fade) {
    if (isDriverEnable()) {
        m_driver->pause(handle, pause, fade);
    }
}

void SoundManager::stopBgmAll() {
    if (isDriverEnable()) {
        m_driver->stopBgmAll();
    }
}

void SoundManager::stopSeAll() {
    if (isDriverEnable()) {
        m_driver->stopSeAll();
    }
}

void SoundManager::fn_71001A0EF8(bool flag) {
    m_dlc = flag;
}

bool SoundManager::isCommonLoaded() const {
    if (m_commonSe != nullptr) {
        return m_commonSe->valid();
    }
    return true;
}

bool SoundManager::isBattleLoaded() const {
    if (m_battleSystemSe != nullptr && !m_battleSystemSe->valid()) {
        return false;
    }
    if (m_battleElemSe != nullptr && !m_battleElemSe->valid()) {
        return false;
    }
    if (m_battleWeaponSe != nullptr && !m_battleWeaponSe->valid()) {
        return false;
    }
    return true;
}

void SoundManager::detachPoolMemory(void* memory, unsigned int size) {
    if (isDriverEnable()) {
        m_driver->detachPoolMemory(memory, size);
    }
}

const char* SoundManager::getName() const {
    return "SoundManager";
}
}  // namespace fw
