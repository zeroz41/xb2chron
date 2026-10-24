#include "classes/fw/PointerMap.h"
#include "classes/ssd/SoundHandle.h"
#include "classes/ssd/SoundActor3D.h"
#include "classes/fw/SoundSsdSource.h"
#include "classes/fw/ISoundDriver.h"
#include "classes/fw/SoundSsdDriver.h"
#include "classes/fw/SoundSsdPlayer.h"
#include "classes/ssd/SoundHandle.h"
#include "classes/ssd/SoundActor3D.h"
#include "classes/fw/ISoundDriver.h"
#include "classes/fw/SoundSsdDriver.h"
#include "classes/fw/SoundSsdDriver/SoundAllocator.h"
#include "classes/fw/SoundSsdPlayer.h"
#include "classes/ssd/SoundBank.h"
#include "classes/fw/SoundSsdBank.h"
#include "classes/fw/SoundReferenceObject.h"
#include "classes/fw/SoundPack.h"
#include "mm/MMStdBase.h"
#include "mtl/MemManager.h"

#define SOUND_SSD_DRV_PATH "D:/Monolithsoft/BF2/prog/application/BF2/framework/sound/sound_ssd_drv.cpp"

namespace fw {

void* SoundSsdDriver::SoundAllocator::AllocInstance(unsigned long size) {
    return m_allocator->allocate(size, 0x10);
}

void SoundSsdDriver::SoundAllocator::FreeInstance(void* address) {
    if (address != nullptr) {
        m_allocator->deallocate(address);
    }
}

void* SoundSsdDriver::SoundAllocator::AllocBuffer(unsigned long size, unsigned long alignment) {
    return m_allocator->allocate(size, alignment);
}

void SoundSsdDriver::SoundAllocator::FreeBuffer(void* address) {
    if (address != nullptr) {
        m_allocator->deallocate(address);
    }
}

void* SoundSsdDriver::SoundAllocator::AllocStream(unsigned long size, unsigned long alignment) {
    return m_allocator->allocate(size, alignment);
}

void SoundSsdDriver::SoundAllocator::FreeStream(void* address) {
    if (address != nullptr) {
        m_allocator->deallocate(address);
    }
}

int SoundReferenceObject::release() {
#line 274 SOUND_SSD_DRV_PATH
    MM_ASSERT(m_RefCount > 0);
    int count = --m_RefCount;
    if (count == 0) {
        this->~SoundReferenceObject();
        mtl::MemManager::deallocate(this, 0, false);
    }
    return count;
}

void SoundSsdBank::stopAll() {
    m_bank.Stop(0.0f);
}

const mm::Mat44& SoundSsdDriver::getListeningPoint() const {
    return m_listeningPoint;
}

bool SoundSsdDriver::startBgm(unsigned int handle) {
    ml::CS lock(m_cs);
    SoundSsdPlayer* player = static_cast<SoundSsdPlayer*>(m_players.getPtr(handle));
    if (player != nullptr && player->isReady()) {
        return player->start();
    }
    return false;
}

bool SoundSsdDriver::stopSound(unsigned int handle, float fadeTime) {
    SoundSsdPlayer* player = getPlayer(handle);
    if (player == nullptr) {
        return false;
    }
    player->stop(fadeTime);
    return true;
}

void SoundSsdDriver::stopSoundAll(SoundType type, float fadeTime) {
    for (PtrMapIterator it = m_players.begin(); it != m_players.end(); ++it) {
        const SoundSsdPlayer* player = static_cast<const SoundSsdPlayer*>(it.m_param->m_ptr);
        if (player != nullptr) {
            unsigned int handle = player->m_soundHandle;
            if ((handle >> 24) == static_cast<unsigned int>(type)) {
                stopSound(handle, fadeTime);
            }
        }
    }
}

bool SoundSsdDriver::stopBgm(unsigned int handle, float fadeTime) {
    ml::CS lock(m_cs);
    return stopSound(handle, fadeTime);
}

void SoundSsdDriver::stopBgmAll() {
    ml::CS lock(m_cs);
    stopSoundAll(static_cast<SoundType>(1), 0.0f);
}

bool SoundSsdDriver::startVoice(unsigned int handle) {
    ml::CS lock(m_cs);
    SoundSsdPlayer* player = static_cast<SoundSsdPlayer*>(m_players.getPtr(handle));
    if (player != nullptr && player->isReady()) {
        return player->start();
    }
    return false;
}

bool SoundSsdDriver::stopVoice(unsigned int handle, float fadeTime) {
    ml::CS lock(m_cs);
    return stopSound(handle, fadeTime);
}

void SoundSsdDriver::stopVoiceAll() {
    ml::CS lock(m_cs);
    stopSoundAll(static_cast<SoundType>(2), 0.0f);
}

bool SoundSsdDriver::stopSe(unsigned int handle, float fadeTime) {
    ml::CS lock(m_cs);
    return stopSound(handle, fadeTime);
}

void SoundSsdDriver::stopSeAll() {
    ml::CS lock(m_cs);
    stopSoundAll(static_cast<SoundType>(3), 0.0f);
}

bool SoundSsdDriver::isValid(unsigned int handle) const {
    ml::CS lock(m_cs);
    return m_players.isValid(handle);
}

bool SoundSsdDriver::isPlaying(unsigned int handle) const {
    ml::CS lock(m_cs);
    const SoundSsdPlayer* player = getPlayer(handle);
    return player != nullptr && player->isPlaying();
}

bool SoundSsdDriver::isReady(unsigned int handle) const {
    ml::CS lock(m_cs);
    const SoundSsdPlayer* player = getPlayer(handle);
    return player != nullptr && player->isReady();
}

bool SoundSsdDriver::isPreparing(unsigned int handle) const {
    ml::CS lock(m_cs);
    const SoundSsdPlayer* player = getPlayer(handle);
    return player != nullptr && player->isPreparing();
}

bool SoundSsdDriver::isPause(unsigned int handle) const {
    ml::CS lock(m_cs);
    const SoundSsdPlayer* player = getPlayer(handle);
    return player != nullptr && player->isPause();
}

void SoundSsdDriver::setCategory(unsigned int handle, SoundCategory category) {
    ml::CS lock(m_cs);
    if (m_players.isValid(handle)) {
        if (SoundSsdPlayer* player = getPlayer(handle)) {
            player->setCategory(category);
        }
    }
}

SoundCategory SoundSsdDriver::getCategory(unsigned int handle) {
    ml::CS lock(m_cs);
    if (m_players.isValid(handle)) {
        if (SoundSsdPlayer* player = getPlayer(handle)) {
            return player->m_category;
        }
    }
    return static_cast<SoundCategory>(0);
}

bool SoundSsdDriver::setPlayTime(unsigned int handle, float time) {
    ml::CS lock(m_cs);
    if (m_players.isValid(handle)) {
        if (SoundSsdPlayer* player = getPlayer(handle)) {
            return player->setPlayTime(time);
        }
    }
    return false;
}

bool SoundSsdDriver::getPlayTime(unsigned int handle, float& time) {
    ml::CS lock(m_cs);
    time = 0.0f;
    if (m_players.isValid(handle)) {
        if (SoundSsdPlayer* player = getPlayer(handle)) {
            return player->getPlayTime(time);
        }
    }
    return false;
}

bool SoundSsdDriver::getTotalTime(unsigned int handle, float& time) {
    ml::CS lock(m_cs);
    time = 0.0f;
    if (m_players.isValid(handle)) {
        if (SoundSsdPlayer* player = getPlayer(handle)) {
            return player->getTotalTime(time);
        }
    }
    return false;
}

bool SoundSsdDriver::setRemainLoopCount(unsigned int handle, int count) {
    ml::CS lock(m_cs);
    if (m_players.isValid(handle)) {
        if (SoundSsdPlayer* player = getPlayer(handle)) {
            return player->setRemainLoopCount(count);
        }
    }
    return false;
}

bool SoundSsdDriver::getRemainLoopCount(unsigned int handle, int& count) {
    ml::CS lock(m_cs);
    count = 0;
    if (m_players.isValid(handle)) {
        if (SoundSsdPlayer* player = getPlayer(handle)) {
            return player->getRemainLoopCount(count);
        }
    }
    return false;
}

bool SoundSsdDriver::isLoop(unsigned int id, SoundPack* pack) {
    if (pack == nullptr) {
        return false;
    }
    ml::CS lock(m_cs);
    mm::mtl::IntrusivePtr<SoundSsdSource> source = pack->findSourceFromID(id);
    if (!source) {
        return false;
    }
    return source->isLoop();
}

bool SoundSsdDriver::isLoop(unsigned int handle) {
    ml::CS lock(m_cs);
    if (m_players.isValid(handle)) {
        if (SoundSsdPlayer* player = getPlayer(handle)) {
            return player->isLoop();
        }
    }
    return false;
}

void SoundSsdDriver::setVolume(unsigned int handle, float volume, float fadeTime) {
    ml::CS lock(m_cs);
    if (m_players.isValid(handle)) {
        if (SoundSsdPlayer* player = getPlayer(handle)) {
            player->setVolume(volume, fadeTime);
        }
    }
}

float SoundSsdDriver::getVolume(unsigned int handle, SoundVolumeType type) {
    ml::CS lock(m_cs);
    if (m_players.isValid(handle)) {
        if (SoundSsdPlayer* player = getPlayer(handle)) {
            return player->getVolume(type);
        }
    }
    return 0.0f;
}

void SoundSsdDriver::setPitch(unsigned int handle, float pitch, float fadeTime) {
    ml::CS lock(m_cs);
    if (m_players.isValid(handle)) {
        if (SoundSsdPlayer* player = getPlayer(handle)) {
            player->setPitch(pitch, fadeTime);
        }
    }
}

void SoundSsdDriver::setPan(unsigned int handle, float pan, float fadeTime) {
    ml::CS lock(m_cs);
    if (m_players.isValid(handle)) {
        if (SoundSsdPlayer* player = getPlayer(handle)) {
            player->setPan(pan, fadeTime);
        }
    }
}

void SoundSsdDriver::setPos(unsigned int handle, const mm::Vec3& pos) {
    ml::CS lock(m_cs);
    if (m_players.isValid(handle)) {
        if (SoundSsdPlayer* player = getPlayer(handle)) {
            if (player->is3DSource()) {
                player->setListener(m_listener);
                player->setPos(pos);
            }
        }
    }
}

void SoundSsdDriver::pause(unsigned int handle, bool pause, float fadeTime) {
    ml::CS lock(m_cs);
    if (m_players.isValid(handle)) {
        if (SoundSsdPlayer* player = getPlayer(handle)) {
            player->pause(pause, fadeTime);
        }
    }
}

void SoundSsdDriver::pauseCategory(SoundCategory category, bool pause, float fadeTime) {
    ml::CS lock(m_cs);
    for (PtrMapIterator it = m_players.begin(); it != m_players.end(); ++it) {
        SoundSsdPlayer* player = static_cast<SoundSsdPlayer*>(const_cast<void*>(it.m_param->m_ptr));
        if (player != nullptr && player->m_category == category) {
            player->pause(pause, fadeTime);
        }
    }
}

void SoundSsdDriver::pauseAll(bool pause, float fadeTime) {
    ml::CS lock(m_cs);
    for (PtrMapIterator it = m_players.begin(); it != m_players.end(); ++it) {
        if (SoundSsdPlayer* player = static_cast<SoundSsdPlayer*>(const_cast<void*>(it.m_param->m_ptr))) {
            player->pause(pause, fadeTime);
        }
    }
}

void ISoundDriver::attachPoolMemory(void*, unsigned int) {}

void ISoundDriver::detachPoolMemory(void*, unsigned int) {}

}  // namespace fw
