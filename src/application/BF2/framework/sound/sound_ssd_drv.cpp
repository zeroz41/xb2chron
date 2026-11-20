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
#include "classes/fw/FrameworkMemory.h"
#include "classes/fw/SoundManager.h"
#include "classes/ssd/SoundListener.h"
#include "classes/fw/SoundPoolMemory.h"
#include "classes/fw/SsdObjectAllocator.h"
#include "classes/ssd/Delegate/Object.h"
#include "ml/PathUtil.h"
#include "mm/mtl/StrUtil.h"
#include "classes/fw/SoundPlayInfo.h"
#include "classes/fw/SoundResult.h"

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

SoundSsdSource::SoundSsdSource(const SetupInfo& info)
    : m_wave(nullptr), m_entry(nullptr), m_bankId(info.bankId), m_name(info.name), m_label(), m_labelHash(0),
      m_uniqueId(0), m_isStream(false), m_is3D(false), pad_240_2(0), pad_244(6) {
    m_nameHash = mm::mtl::hashStrCrc(m_name.m_str);
    m_label = ml::PathUtil::getFilePtrFromPath(info.name);
    m_labelHash = mm::mtl::hashStrCrc(m_label.m_str);
    m_bank = SoundSsdDriver::sys()->findBank(m_bankId);
}

SoundSsdSource::SoundSsdSource(const SetupWaveInfo& info)
    : m_wave(nullptr), m_entry(nullptr), m_bankId(info.bankId), m_name(info.name), m_label(), m_labelHash(0),
      m_uniqueId(0), m_isStream(false), m_is3D(false), pad_240_2(0), pad_244(6) {
    m_nameHash = mm::mtl::hashStrCrc(m_name.m_str);
    if (info.label != nullptr && info.label[0] != '\0') {
        m_label = info.label;
        m_labelHash = mm::mtl::hashStrCrc(m_label.m_str);
    }
    m_bank = SoundSsdDriver::sys()->findBank(m_bankId);
}

SoundSsdSource::~SoundSsdSource() {
    if (m_bank != nullptr && m_entry != nullptr) {
        m_bank->m_bank.RemoveSoundEntry(m_entry);
    }
    if (m_entry != nullptr) {
        m_entry->~SoundEntry();
        mtl::MemManager::deallocate(m_entry, 0, false);
        m_entry = nullptr;
    }
    if (m_wave != nullptr) {
        m_wave->~WaveSource();
        mtl::MemManager::deallocate(m_wave, 0, false);
        m_wave = nullptr;
    }
    mm::mtl::List<SoundSsdSource*>& sources = m_bank->m_sources;
    mm::mtl::List<SoundSsdSource*>::iterator end = sources.end();
    for (mm::mtl::List<SoundSsdSource*>::iterator it = sources.begin(); it != end;) {
        if (*it == this) {
            it = sources.erase(it);
        } else {
            ++it;
        }
    }
}

SoundSsdPlayer::SoundSsdPlayer(const SoundPlayerSetupParam& param)
    : m_setup(param), m_soundHandle(0), pad_bc(-1.0f), m_flags(0), m_pauseCount(0) {
    m_actor.Init();
    m_actor.SetVolume(1.0f, 0.0f);
    m_actor.SetListener(param.listener);
    m_actor.SetPosition(ssd::Vec3{0.0f, 0.0f, 0.0f});
    m_actor.SetVelocity(ssd::Vec3{0.0f, 0.0f, 0.0f});
    m_actor.SetCategoryId(param.category);
    if (param.source->m_isStream) {
        m_flags |= 0x4;
    }
    if (param.listener != nullptr) {
        m_flags |= 0x8;
    } else {
        m_flags &= ~0x8;
    }
}

SoundSsdBank::SoundSsdBank(const SoundBankSetup& setup) : m_allocator(setup.allocator) {
    m_id = setup.id;
    m_name = setup.name;
    m_nameHash = mm::mtl::hashStrCrc(m_name.m_str);
    pad_150 = setup.pad_18;
    unsigned int count = setup.maxSound < 256 ? 256 : setup.maxSound;
    m_sources.setAllocator(m_allocator);
    m_sources.reserve(count);
    m_bank.Init(m_id, ssd::TextRef(m_name.m_str));
    m_group.id_ = 0;
    m_group.maxSound_ = 256;
    setMaxSound(setup.maxSound);
    m_bank.AddSoundGroup(&m_group);
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

void SoundSsdBank::update() {
    for (mm::mtl::List<SoundSsdSource*>::iterator it = m_sources.begin(); it != m_sources.end();) {
        SoundSsdSource* source = *it;
        if (source->m_RefCount == 1 && (source->m_wave == nullptr || source->m_wave->referenceCount_ == 0)) {
            it = m_sources.erase(it);
            source->release();
        } else {
            ++it;
        }
    }
}

//the log method SoundCore::Init installs: drops every message
float SoundSsdDriver::getBgmVolume(const char* name) {
    if (name == nullptr) {
        return 1.0f;
    }
    const char* base = name;
    for (const char* p = name; *p != '\0'; ++p) {
        switch (*p) {
        case '/':
        case '\\':
            base = p + 1;
            break;
        }
    }
    // the row lives outside the loop (a loop-scoped one gives its exit a cleanup the original does not have)
    int row = 0;
    for (; row < m_bgmVolumes->GetRowCount(); ++row) {
        const char* entry = m_bgmVolumes->GetString(row, 0);
        const char* p = base;
        for (;;) {
            char c = *p++;
            char e = *entry++;
            if ((c == '.' || c == '\0') && e == '\0') {
                return m_bgmVolumes->GetFloat(row, 1);
            }
            if (c != e) {
                break;
            }
        }
    }
    return 1.0f;
}

static ssd::Result fn_71001A384C(ssd::LogMessage::Type, const char16_t*) {
    return ssd::Result(0);
}

SoundSsdDriver::SoundSsdDriver(mm::mtl::IAllocator* allocator, unsigned int handleCount)
    : m_core(nullptr), m_allocator(allocator), m_listener(nullptr), m_initialized(false) {
    m_core = ssd::SoundCore::NewInstance(&m_allocator);
    m_listeningPoint = mm::Mat44::identity;
    ssd::SoundCore::InitParam param;
    param.audioThread.coreMask = 2;
    param.streamThread.coreMask = 2;
    param.voiceNum = 0x40;
    param.messageMethod = fn_71001A384C;
    param.timeStampType = ssd::LogTimeStamp::Type(1);
    m_core->Init(param);
#line 1501 SOUND_SSD_DRV_PATH
    m_listener = new (FrameworkMemory::getAllocator(5), 8, __FILE__, __LINE__) ssd::SoundListener();
    m_listener->Init();
    {
        CategoryInfo info;
        for (int i = 0; i < 18; i++) {
            m_categories[i] = info;
        }
    }
    m_banks.setAllocator(allocator);
    m_banks.reserve(0x200);
    m_handles.setAllocator(allocator);
    m_handles.reserve(handleCount);
    m_handlePlayers.setAllocator(allocator);
    mm::Mat44 point = mm::Mat44::identity;
    setListeningPoint(point);
    m_handleAllocator.reserve(allocator, handleCount);
    m_players.reserve(allocator, handleCount);
    m_players.setRange(1, 0xFFFFFF, 0xFFFFFF);
#line 1529 SOUND_SSD_DRV_PATH
    m_bgmVolumes = new (FrameworkMemory::getAllocator(5), 16, __FILE__, __LINE__) csvb::CCsvbData();
    reloadBgmVolume(-1);
    pad_1b64 = 1;
    m_initialized = true;
}

void SoundSsdDriver::reloadBgmVolume(int dlc) {
    SoundManager* manager = SoundManager::sys();
    if (dlc < 0) {
        dlc = manager->m_dlc;
    }
    if (dlc != 0) {
        m_bgmVolumes->Load(manager->getProcAllocator(), "sound/ira_vol.csvb");
    } else {
        m_bgmVolumes->Load(manager->getProcAllocator(), "sound/bgm_vol.csvb");
    }
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

void SoundSsdDriver::attachPoolMemory(void* memory, unsigned int size) {
    ml::CS lock(m_cs2);
    for (mm::mtl::FixedList<SoundPoolMemory*, 256>::iterator it = m_poolMemories.begin();
         it != m_poolMemories.end(); ++it) {
        if ((*it)->m_memory == memory && (*it)->m_size == size) {
            return;
        }
    }
#line 1569 SOUND_SSD_DRV_PATH
    SoundPoolMemory* pool = new (FrameworkMemory::getAllocator(5), 8, __FILE__, __LINE__) SoundPoolMemory(memory, size);
    m_poolMemories.push_back(pool);
}

void SoundSsdDriver::detachPoolMemory(void* memory, unsigned int size) {
    ml::CS lock(m_cs2);
    // the walk stops on the pool, which is detached after it
    mm::mtl::FixedList<SoundPoolMemory*, 256>::iterator it = m_poolMemories.begin();
    SoundPoolMemory* pool = nullptr;
    for (; it != m_poolMemories.end(); ++it) {
        pool = *it;
        if (pool->m_memory == memory && pool->m_size == size) {
            break;
        }
    }
    if (it != m_poolMemories.end()) {
        pool->detach();
    }
}

void SoundSsdDriver::updatePoolMemory() {
    ml::CS lock(m_cs2);
    for (mm::mtl::FixedList<SoundPoolMemory*, 256>::iterator it = m_poolMemories.begin();
         it != m_poolMemories.end(); ++it) {
        SoundPoolMemory* pool = *it;
        if (pool->m_state == 2) {
            pool->release();
            it = m_poolMemories.erase(it);
            if (pool != nullptr) {
                SsdObjectAllocator::deleteObject(pool);
            }
        }
    }
}

void SoundSsdDriver::releaseHandle(ssd::SoundHandle* handle) {
    if (handle == nullptr) {
        return;
    }
    ssd::Delegate::Object<SoundSsdDriver, ssd::SoundHandle*, ssd::SoundHandle::Notify::Type> delegate(
        this, &SoundSsdDriver::SoundHandleDelegate);
    ssd::Delegate::Handle* found = handle->notify_.FindDelegate(&delegate);
    if (found != nullptr) {
        handle->RemoveDelegateInternal(found);
        ssd::SoundMemory::allocator_->DeleteInstance(found);
    }
    if (mm::mtl::Map<ssd::SoundHandle*, SoundSsdPlayer*>::node* n = m_handlePlayers.find(handle)) {
        SoundSsdPlayer* player = n->value.second;
        m_players.remove(player->m_soundHandle);
        m_handlePlayers.erase(handle);
        if (player != nullptr) {
            SsdObjectAllocator::deleteObject(player);
        }
    }
    m_handleAllocator.free(handle);
}

void SoundSsdDriver::updateBank() {
    ml::CS lock(m_cs);
    for (mm::mtl::List<SoundSsdBank*>::iterator it = m_banks.begin(); it != m_banks.end();) {
        SoundSsdBank* bank = *it;
        bank->update();
        if (bank->m_RefCount == 1 && bank->m_bank.GetReferenceCounter() == 0 && bank->m_bank.NumSoundEntry() == 0) {
            it = m_banks.erase(it);
            if (bank != nullptr) {
                bank->release();
            }
        } else {
            ++it;
        }
    }
}

void SoundSsdDriver::setListeningPoint(const mm::Mat44& point) {
    if (!isValid() || m_listener == nullptr) {
        return;
    }
    {
        mm::Vec3 position = point.getTrans();
        m_listener->SetPosition(reinterpret_cast<const ssd::Vec3&>(position));
    }
    mm::Vec3 front(point.m[0][0] * 0.0f + point.m[1][0] * 0.0f - point.m[2][0],
                   point.m[0][1] * 0.0f + point.m[1][1] * 0.0f - point.m[2][1],
                   point.m[0][2] * 0.0f + point.m[1][2] * 0.0f - point.m[2][2]);
    float length = front.length();
    if (length <= 1e-6f) {
        front = mm::Vec3::zero;
    } else {
        float scale = 1.0f / length;
        front.x = front.x * scale;
        front.y = front.y * scale;
        front.z = scale * front.z;
    }
    m_listener->SetOrientation(ssd::Vec3(reinterpret_cast<const ssd::Vec3&>(front)), ssd::Vec3{0.0f, 1.0f, 0.0f});
    m_listeningPoint = point;
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
            return player->m_setup.category;
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
        if (player != nullptr && player->m_setup.category == category) {
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

void SoundSsdDriver::setCategoryMute(SoundCategory category, bool mute, float fadeTime) {
    if (m_core == nullptr) {
        return;
    }
    CategoryInfo* info = findCategory(category);
    if (info == categoryEnd()) {
        return;
    }
    if (!mute && info->muteCount == 0) {
        return;
    }
    if (info->active != 0) {
        if (mute) {
            if (info->muteCount == 0) {
                info->mute.set(0.0f, fadeTime);
            }
            info->muteCount++;
        } else {
            info->muteCount--;
            if (info->muteCount == 0) {
                info->mute.set(1.0f, fadeTime);
            }
        }
    }
    info->applyVolume();
    m_core->SetCategory(info->category);
}

void SoundSsdDriver::setCategoryVolume(SoundCategory category, float volume, float fadeTime) {
    if (m_core == nullptr) {
        return;
    }
    CategoryInfo* info = findCategory(category);
    if (info == categoryEnd()) {
        return;
    }
    if (info->active != 0) {
        info->active = 1;
        info->volume.set(volume, fadeTime);
        // applyVolume's product, the new volume first (it keeps the original's operand order)
        float value = info->volume.current * (info->masterVolume * info->baseVolume);
        info->category.volume_ = value * info->mute.current;
    }
    m_core->SetCategory(info->category);
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
        if (player != nullptr && player->m_setup.category == category && player->isValid()) {
            player->m_setup.pitchRate = pitch;
            player->m_setup.handle->SetPitch(pitch, fadeTime);
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

unsigned int SoundSsdDriver::playSeLocal(mm::mtl::IntrusivePtr<SoundSsdSource> source, SoundPack* pack, float volume,
                                         SoundCategory category) {
    if (source && source.get()->m_entry != nullptr) {
        ssd::SoundHandle* handle = m_handleAllocator.allocate();
        if (handle != nullptr) {
            handle->Init();
            SoundPlayerSetupParam param;
            param.allocator = FrameworkMemory::getAllocator(5);
            param.source = source;
            param.handle = handle;
            param.volume = volume;
            param.bankId = source->m_bankId;
            param.type = static_cast<SoundType>(3);
            if (category == 0) {
                category = pack->m_category;
            }
            param.category = category;
#line 2706 SOUND_SSD_DRV_PATH
            SoundSsdPlayer* player = new (FrameworkMemory::getAllocator(5), 8, __FILE__, __LINE__) SoundSsdPlayer(param);
            if (player != nullptr) {
                unsigned int id = m_players.regist(player) | 0x3000000;
                m_handlePlayers.insert(mm::mtl::MapPair<ssd::SoundHandle*, SoundSsdPlayer*>(handle, player));
                player->m_soundHandle = id;
                ssd::Delegate::Object<SoundSsdDriver, ssd::SoundHandle*, ssd::SoundHandle::Notify::Type>* delegate =
                    ssd::SoundMemory::allocator_->NewInstance<
                        ssd::Delegate::Object<SoundSsdDriver, ssd::SoundHandle*, ssd::SoundHandle::Notify::Type> >();
                delegate->method_ = &SoundSsdDriver::SoundHandleDelegate;
                delegate->object_ = this;
                handle->AddDelegateInternal(delegate);
                ssd::Result result = player->m_actor.Play(player->m_setup.handle, player->m_setup.source->m_entry,
                                                          player->m_setup.volume, 0.0f);
                if (player->isValid()) {
                    player->m_setup.handle->SetCategoryId(player->m_setup.category);
                }
                if (result >= 0) {
                    return id;
                }
                handle->Stop(0.0f);
            }
            releaseHandle(handle);
        }
    }
    return 0;
}

unsigned int SoundSsdDriver::playSe(const char* name, SoundPack* pack, float volume, SoundCategory category) {
    if (pack == nullptr) {
        return 0;
    }
    ml::CS lock(m_cs);
    mm::mtl::IntrusivePtr<SoundSsdSource> source = pack->findSource(name);
    if (!source) {
        return 0;
    }
    return playSeLocal(source, pack, volume, category);
}

unsigned int SoundSsdDriver::playSe(unsigned int id, SoundPack* pack, float volume, SoundCategory category) {
    if (pack == nullptr) {
        return 0;
    }
    ml::CS lock(m_cs);
    mm::mtl::IntrusivePtr<SoundSsdSource> source = pack->findSourceFromID(id);
    if (!source) {
        return 0;
    }
    return playSeLocal(source, pack, volume, category);
}

unsigned int SoundSsdDriver::playSeEx(const SoundPlayInfo& info, SoundResult& result) {
    result.handle = 0;
    result.status = 3;
    if (info.pack == nullptr) {
        return 0;
    }
    ml::CS lock(m_cs);
    mm::mtl::IntrusivePtr<SoundSsdSource> source = info.pack->findSourceFromID(info.id);
    if (source) {
        result.handle = playSeLocal(source, info.pack, info.volume, info.category);
        result.status = result.handle != 0 ? 0 : 3;
        if (info.hasPos) {
            setPos(result.handle, info.pos);
        }
    }
    return result.handle;
}

bool SoundSsdDriver::findSe(const char* name) const {
    ml::CS lock(m_cs);
    for (PtrMapIterator it = m_players.begin(); it != m_players.end();) {
        const SoundSsdPlayer* player = static_cast<const SoundSsdPlayer*>(it.m_param->m_ptr);
        ++it;
        if (player != nullptr && player->m_setup.type == 3 && strcmp(player->m_setup.source->m_label.m_str, name) == 0) {
            return true;
        }
    }
    return false;
}

void ISoundDriver::attachPoolMemory(void*, unsigned int) {}

void ISoundDriver::detachPoolMemory(void*, unsigned int) {}

}  // namespace fw

// playStream/playSeLocal (not written yet) add a handle's player
template mm::mtl::Map<ssd::SoundHandle*, fw::SoundSsdPlayer*>::node* mm::mtl::Map<ssd::SoundHandle*, fw::SoundSsdPlayer*>::tree_type::insert(const mm::mtl::Map<ssd::SoundHandle*, fw::SoundSsdPlayer*>::tree_type::value_type&);

// FixStr<256>'s insert (its caller is not written yet)
template mm::mtl::FixStr<256>& mm::mtl::FixStr<256>::insert(int, const char*, int);

// playStream (not written yet) replaces in a stream's name; playStream and playSeLocal allocate a handle
template void mm::mtl::replacestr<mm::mtl::FixStr<256> >(mm::mtl::FixStr<256>&, const char*, const char*);
template ssd::SoundHandle* mm::mtl::ObjectAllocator<ssd::SoundHandle>::allocate();
