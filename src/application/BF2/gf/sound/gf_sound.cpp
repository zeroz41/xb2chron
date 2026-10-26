#include "classes/ml/fixed_size_alloc_inside.h"
#include "gf/SoundHandle.h"
#include "gf/SoundParam.h"
#include "classes/gf/GfSound.h"
#include "classes/gf/GfSound.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfEvent.h"
#include "classes/fw/SoundManager.h"
#include "classes/fw/SoundPack.h"

namespace gf {

void SoundParam::clear() {
    m_id = 0;
    m_name.clear();
    m_volume = 1.0f;
    m_kind = 0;
    m_transform = 0;
    pad_3a = 0;
    m_obj = reinterpret_cast<GF_OBJ_HANDLE*>(-1);
}

void SoundHandle::clear() {
    m_id = 0;
    m_seIndex = 0xFFFF;
}

SoundHandle::SoundHandle() {
    clear();
}

SoundHandle::SoundHandle(unsigned int id) : m_id(id), m_seIndex(0xFFFF) {}

bool SoundHandle::isValid() const {
    return m_id != 0;
}

// GfSound's constructor below inlines it; the out-of-line copy (0x7100570CC8) is another unit's
inline GfMasterVolume::GfMasterVolume()
    : m_eventVoiceVolume(0.7f), m_eventCsVolume(0.8f), m_eventBgmVolume(0.6f), m_eventSeVolume(0.7f),
      m_gameBgmVolume(0.6f), m_gameEnvVolume(0.4f), m_gameWeatherVolume(0.4f), m_gameSeVolume(0.6f),
      m_playerVoiceVolume(0.8f), m_enemyVoiceVolume(0.8f), m_nareVoiceVolume(0.8f), m_systemVolume(0.5f),
      m_menuBgmVolume(0.5f) {
    if (GfManager::fn_710032A1DC()) {
        m_eventVoiceVolume = 0.75f;
        m_eventBgmVolume = 0.8f;
        m_gameBgmVolume = 0.8f;
    }
}

void GfMasterVolume::initialize() {
    if (GfSound* sound = GfSound::get()) {
        m_handle = sound->createCategoryHandle();
    }
}

void GfMasterVolume::finalize() {
    if (GfSound* sound = GfSound::get()) {
        sound->releaseCategoryHandle(m_handle);
    }
}

GfSound::GfSound(const GfSetupParam& param)
    : m_isEnable(false), m_isVolumeDirty(false), pad_18(0),
      m_categoryHandle(reinterpret_cast<GF_SE_CATEGORY_HANDLE*>(-1)) {
    initialize(param);
}

void GfSound::initialize(const GfSetupParam& param) {
    GfEvent::addEventCallback(this);
    m_masterVolume.initialize();
    m_categoryHandle = createCategoryHandle();
    m_isEnable = true;
}

GfSound::~GfSound() {}

void GfSound::build(const GfSetupParam& param) {
#line 166
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfSound(param);
}

void GfSound::destroy() {
    GfSound* self = get();
    self->finalize();
    delete self;
}

void GfSound::finalize() {
    releaseCategoryHandle(m_categoryHandle);
    m_masterVolume.finalize();
    GfEvent::removeEventCallback(this);
    m_isEnable = false;
}

void GfSound::setupGame() {
    m_masterVolume.setupGame();
}

void GfSound::setCategoryVolume(GF_SE_CATEGORY_HANDLE* handle, fw::SoundCategory category, float volume, float time) {
    m_categoryVolumes[static_cast<unsigned char>(reinterpret_cast<unsigned long>(handle))].m_volumes[static_cast<unsigned int>(category)].set(
        volume, time);
}

float GfSound::getCategoryVolume(GF_SE_CATEGORY_HANDLE* handle, fw::SoundCategory category) const {
    return m_categoryVolumes[static_cast<unsigned char>(reinterpret_cast<unsigned long>(handle))]
        .m_volumes[static_cast<unsigned int>(category)]
        .current;
}

void GfSound::setCategoryPitch(fw::SoundCategory category, float pitch, float time) {
    if (fw::SoundManager* manager = fw::SoundManager::get()) {
        manager->setCategoryPitch(category, pitch, time);
    }
}

void GfSound::stopBgm(SoundHandle handle, float time) {
    if (fw::SoundManager* manager = fw::SoundManager::get()) {
        manager->stopBgm(handle.m_id, time);
    }
}

SoundHandle GfSound::playVoice(const char* path, float volume, bool loop, fw::SoundCategory category) {
    if (fw::SoundManager* manager = fw::SoundManager::get()) {
        return SoundHandle(manager->playVoice(path, volume, loop, category));
    }
    return SoundHandle();
}

void GfSound::stopVoice(SoundHandle handle, float time) {
    if (fw::SoundManager* manager = fw::SoundManager::get()) {
        manager->stopVoice(handle.m_id, time);
    }
}

void GfSound::stopSe(SoundHandle handle, float time) {
    if (fw::SoundManager* manager = fw::SoundManager::get()) {
        manager->stopSe(handle.m_id, time);
    }
}

void GfSound::setCategory(SoundHandle handle, fw::SoundCategory category) {
    if (getSeParam(handle.m_seIndex) != nullptr) {
        if (fw::SoundManager* manager = fw::SoundManager::get()) {
            manager->setCategory(handle.m_id, category);
        }
    }
}

void GfSound::setPause(SoundHandle handle, bool pause, float time) {
    setPauseType(handle, pause, time, 1);
}

void GfSound::setPan(SoundHandle handle, float pan, float time) {
    if (fw::SoundManager* manager = fw::SoundManager::get()) {
        manager->setPan(handle.m_id, pan, time);
    }
}

bool GfSound::setPlayTime(SoundHandle handle, float time) {
    if (fw::SoundManager* manager = fw::SoundManager::get()) {
        return manager->setPlayTime(handle.m_id, time);
    }
    return false;
}

bool GfSound::getPlayTime(SoundHandle handle, float& time) const {
    if (fw::SoundManager* manager = fw::SoundManager::get()) {
        return manager->getPlayTime(handle.m_id, time);
    }
    return false;
}

bool GfSound::getTotalTime(SoundHandle handle, float& time) const {
    if (fw::SoundManager* manager = fw::SoundManager::get()) {
        return manager->getTotalTime(handle.m_id, time);
    }
    return false;
}

void GfSound::setVolume(SoundHandle handle, float volume, float time) {
    if (fw::SoundManager* manager = fw::SoundManager::get()) {
        manager->setVolume(handle.m_id, volume, time);
    }
}

float GfSound::getVolume(SoundHandle handle) {
    if (fw::SoundManager* manager = fw::SoundManager::get()) {
        return manager->getVolume(handle.m_id, static_cast<fw::SoundVolumeType>(0));
    }
    return 0.0f;
}

bool GfSound::isPlaying(SoundHandle handle) const {
    if (fw::SoundManager* manager = fw::SoundManager::get()) {
        return manager->isPlaying(handle.m_id);
    }
    return false;
}

bool GfSound::isPreparing(SoundHandle handle) const {
    if (fw::SoundManager* manager = fw::SoundManager::get()) {
        return manager->isPreparing(handle.m_id);
    }
    return false;
}

void GfSound::destroyObjSePack(fw::SoundPack*& pack) {
    if (pack != nullptr) {
        pack->release();
        pack = nullptr;
    }
}

void GfSound::gevPause(unsigned int resume, unsigned int pause) {
    if (pause & 8) {
        setPauseGameSe(true);
        setPauseGameWeatherSe(true);
    }
    if (pause & 4) {
        setPauseEventSe(true);
    }
    if (resume & 8) {
        setPauseGameSe(false);
        setPauseGameWeatherSe(false);
    }
    if (resume & 4) {
        setPauseEventSe(false);
    }
}

void GfSound::gevLayerPause(unsigned int, bool) {}

GfMasterVolume::~GfMasterVolume() {}

void GfMasterVolume::setGameSeVolume(float volume) {
    m_gameSeVolume = volume;
    if (GfSound* sound = GfSound::get()) {
        sound->setCategoryVolume(m_handle, static_cast<fw::SoundCategory>(4), volume, 0.0f);
        sound->setCategoryVolume(m_handle, static_cast<fw::SoundCategory>(5), volume, 0.0f);
        sound->setCategoryVolume(m_handle, static_cast<fw::SoundCategory>(6), volume, 0.0f);
        sound->setCategoryVolume(m_handle, static_cast<fw::SoundCategory>(13), volume, 0.0f);
        sound->setCategoryVolume(m_handle, static_cast<fw::SoundCategory>(14), volume, 0.0f);
        sound->setCategoryVolume(m_handle, static_cast<fw::SoundCategory>(15), volume, 0.0f);
        sound->setCategoryVolume(m_handle, static_cast<fw::SoundCategory>(16), volume, 0.0f);
    }
}

}  // namespace gf
