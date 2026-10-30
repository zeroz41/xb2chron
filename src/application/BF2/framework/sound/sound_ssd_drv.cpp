#include "classes/fw/SoundSsdSource.h"
#include "classes/ssd/SoundEntry.h"
#include "classes/mm/mtl/_ReslistBase.h"
#include "classes/ssd/SoundGroup.h"
#include "classes/fw/SoundSsdBank.h"
#include "classes/ssd/SoundCategory.h"
#include "classes/fw/ISoundDriver.h"
#include "classes/fw/SoundSsdPlayer.h"
#include "classes/fw/SoundSsdBank.h"
#include "classes/fw/SoundSsdDriver.h"
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
#include "classes/ssd/SoundCore.h"
#include "classes/fw/SoundSsdBank.h"
#include "classes/fw/SoundReferenceObject.h"
#include "classes/fw/SoundPack.h"
#include "csvb/CsvbData.h"
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

void SoundSsdBank::setMaxSound(int maxSound) {
    m_group.id_ = m_id;
    m_group.maxSound_ = maxSound;
    m_maxSound = maxSound;
}

SoundSsdBank::~SoundSsdBank() {
    if (m_bank.GetReferenceCounter() == 0) {
        m_bank.NumSoundEntry();
    }
    for (mm::mtl::List<SoundSsdSource*>::iterator it = m_sources.begin(); it != m_sources.end(); ++it) {
    }
    m_sources.freeNodes();
    m_sources.clear();
    m_bank.Quit();
}

void SoundSsdBank::stopAll() {
    m_bank.Stop(0.0f);
}

SoundSsdDriver::~SoundSsdDriver() {
    finalize();
    if (m_bgmVolumes != nullptr) {
        delete m_bgmVolumes;
        m_bgmVolumes = nullptr;
    }
}

bool SoundSsdDriver::isDeviceEnable() const {
    return m_core != nullptr && !m_core->pad_11;
}

void SoundSsdDriver::updateDebugInfo(mm::mtl::FixedVector<SoundHandleDebugInfo, 128ul>&,
                                     mm::mtl::FixedVector<SoundCategoryDebugInfo, 18ul>&) {}

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

void SoundSsdDriver::stopAll() {
    for (mm::mtl::List<SoundSsdBank*>::iterator it = m_banks.begin(); it != m_banks.end(); ++it) {
        (*it)->stopAll();
    }
    if (m_core != nullptr) {
        m_core->StopSound(0.0f);
    }
}

void SoundSsdDriver::destroyResourceAll() {
    while (m_banks.m_size != 0) {
        SoundSsdBank* bank = *m_banks.begin();
        bank->destroy();
        if (bank != nullptr) {
            bank->release();
        }
        m_banks.erase(m_banks.begin());
    }
}

void SoundSsdDriver::setOutputMode(SoundOutputType type) {
    if (m_core != nullptr) {
        int mode;
        if (type >= 1 && type <= 3) {
            mode = type;
        } else if (type == 0) {
            mode = 0;
        } else {
            mode = 2;
        }
        m_core->SetOutputMode(static_cast<ssd::OutputMode::Type>(mode));
    }
}

void SoundSsdDriver::setMasterVolume(float volume) {
    if (m_core != nullptr) {
        for (int i = 1; i < 18; i++) {
            m_categories[i].masterVolume = volume;
            m_core->SetCategory(m_categories[i].category);
        }
    }
}

void SoundSsdDriver::addCategory(SoundCategory category, float volume, const char* name) {
    CategoryInfo& info = m_categories[static_cast<unsigned int>(category)];
    info.baseVolume = volume;
    info.active = 1;
    info.name = name;
    info.muteCount = 0;
    info.category.id_ = category;
    info.pitch = 1.0f;
    info.category.volume_ = volume;
    m_core->SetCategory(info.category);
}

void SoundSsdDriver::removeCategory(SoundCategory category) {
    if (findCategory(category) != categoryEnd()) {
        m_categories[static_cast<unsigned int>(category)].category.id_ = 0;
        m_categories[static_cast<unsigned int>(category)].category.volume_ = 1.0f;
        m_categories[static_cast<unsigned int>(category)].active = 0;
        m_core->ResetCategory(category);
    }
}

float SoundSsdDriver::getCategoryVolume(SoundCategory category) const {
    float volume = 0.0f;
    if (m_core != nullptr) {
        const CategoryInfo* info = findCategory(category);
        if (info != categoryEnd()) {
            volume = info->volume.current;
        }
    }
    return volume;
}

void SoundSsdDriver::setCategoryPitch(SoundCategory category, float pitch, float fadeTime) {
    if (m_core == nullptr) {
        return;
    }
    ml::CS lock(m_cs);
    for (PtrMapIterator it = m_players.begin(); it != m_players.end(); ++it) {
        SoundSsdPlayer* player = static_cast<SoundSsdPlayer*>(const_cast<void*>(it.m_param->m_ptr));
        if (player != nullptr && player->m_category == category && player->isValid()) {
            player->m_pitchRate = pitch;
            player->m_handle->SetPitch(pitch, fadeTime);
        }
    }
    CategoryInfo* info = findCategory(category);
    if (info != categoryEnd()) {
        info->pitch = pitch;
    }
}

// the int is unused
unsigned int SoundSsdDriver::playBgm(const char* name, float volume, bool loop, int, SoundCategory category) {
    ml::CS lock(m_cs);
    return playStream(name, volume, loop, category, static_cast<SoundPriority>(0xFF), findBank("SystemBgmBank"),
                      static_cast<SoundType>(1));
}

unsigned int SoundSsdDriver::playVoice(const char* name, float volume, bool loop, SoundCategory category) {
    ml::CS lock(m_cs);
    return playStream(name, volume, loop, category, static_cast<SoundPriority>(0xFE), findBank("SystemVoiceBank"),
                      static_cast<SoundType>(2));
}

bool SoundSsdDriver::findSe(const char* name) const {
    ml::CS lock(m_cs);
    for (PtrMapIterator it = m_players.begin(); it != m_players.end();) {
        const SoundSsdPlayer* player = static_cast<const SoundSsdPlayer*>(it.m_param->m_ptr);
        ++it;
        if (player != nullptr && player->m_type == 3 && strcmp(player->m_source->m_label.m_str, name) == 0) {
            return true;
        }
    }
    return false;
}

void ISoundDriver::attachPoolMemory(void*, unsigned int) {}

void ISoundDriver::detachPoolMemory(void*, unsigned int) {}

}  // namespace fw
