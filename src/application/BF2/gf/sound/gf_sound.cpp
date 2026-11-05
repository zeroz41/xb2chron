#include "classes/ml/fixed_size_alloc_inside.h"
#include "gf/SoundHandle.h"
#include "gf/SoundParam.h"
#include "classes/gf/GfSound.h"
#include "classes/gf/GfSound.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfEvent.h"
#include "classes/fw/SoundManager.h"
#include "classes/fw/SoundPack.h"
#include "classes/gf/GfBdatBgm.h"
#include "mm/mtl/FixStr.h"
#include "classes/gf/GfFieldSound.h"
#include "classes/gf/GfAssetResource.h"
#include "gf/GfObjUtil.h"
#include "fw/UpdateInfo.h"

namespace gf {

void SoundParam::clear() {
    m_id = 0;
    m_name.clear();
    m_volume = 1.0f;
    m_kind = 0;
    m_transform = 0;
    m_packKind = 0;
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

GfMasterVolume::GfMasterVolume()
    : m_eventVoiceVolume(0.7f), m_eventCsVolume(0.8f), m_eventBgmVolume(0.6f), m_eventSeVolume(0.7f),
      m_gameBgmVolume(0.6f), m_gameEnvVolume(0.4f), m_gameWeatherVolume(0.4f), m_gameSeVolume(0.6f),
      m_playerVoiceVolume(0.8f), m_enemyVoiceVolume(0.8f), m_nareVoiceVolume(0.8f), m_systemVolume(0.5f),
      m_menuBgmVolume(0.5f) {
    if (GfManager::isGameTypeIra()) {
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
    : m_isEnable(false), m_isVolumeDirty(false), m_handleSerial(0),
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

void GfSound::update(const fw::UpdateInfo& info) {
    calcCategoryVolume(info);
    updateSeParamList(info);
    m_isVolumeDirty = false;
}

void GfSound::updateSeParamList(const fw::UpdateInfo& info) {
    if (fw::SoundManager* manager = fw::SoundManager::get()) {
        mm::mtl::FixedList<unsigned short, 512>::iterator it = m_seList.begin();
        while (it != m_seList.end()) {
            if (manager->isValid(m_seParams[*it].m_handle.m_id)) {
                ++it;
            } else {
                deAllocateSeParam(*it);
                it = m_seList.erase(it);
            }
        }
    }
}

GF_SE_CATEGORY_HANDLE* GfSound::createCategoryHandle() {
    for (unsigned int i = 0; i < 32; ++i) {
        if (m_categoryVolumes[i].m_id < 0) {
            int index = i;
            CategoryVolume& volume = m_categoryVolumes[index];
            for (Volume& v : volume.m_volumes) {
                v = Volume();
            }
            volume.m_isFree = true;
            volume.m_id = index;
            GF_SE_CATEGORY_HANDLE* handle =
                reinterpret_cast<GF_SE_CATEGORY_HANDLE*>(static_cast<unsigned long>(i) | m_handleSerial << 8);
            ++m_handleSerial;
            return handle;
        }
    }
    return reinterpret_cast<GF_SE_CATEGORY_HANDLE*>(-1);
}

void GfSound::releaseCategoryHandle(GF_SE_CATEGORY_HANDLE*& handle) {
    if (handle != reinterpret_cast<GF_SE_CATEGORY_HANDLE*>(-1)) {
        CategoryVolume& volume = m_categoryVolumes[static_cast<unsigned char>(reinterpret_cast<unsigned long>(handle))];
        for (Volume& v : volume.m_volumes) {
            v = Volume();
        }
        volume.m_isFree = true;
        volume.m_id = -1;
        m_isVolumeDirty = true;
        handle = reinterpret_cast<GF_SE_CATEGORY_HANDLE*>(-1);
    }
}

void GfSound::setupGame() {
    m_masterVolume.setupGame();
}

GfSound::CategoryVolume::CategoryVolume() : m_id(-1), m_isFree(true) {
    for (Volume& volume : m_volumes) {
        volume = Volume();
    }
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

SoundHandle GfSound::playBgm(unsigned int id, float time, bool loop, int param, fw::SoundCategory category) {
    const char* name = GfBdatBgm::get()->getBgmListfilename(id);
    if (name == nullptr || name[0] == '\0') {
        return SoundHandle();
    }
    mm::mtl::FixStr<128> path;
    path.format("stream/bgm/%s", name);
    return playBgm(path.m_str, time, loop, param, category);
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

SoundHandle GfSound::playSe(const SoundParam& param) {
    if (fw::SoundManager* manager = fw::SoundManager::get()) {
        mm::mtl::FixedVector<fw::SoundPack*, 4> packs;
        if (param.m_packKind != 0) {
            if (getSePack(packs, param)) {
                return playSeWithPack(param, packs, static_cast<SEINFO>(param.m_packKind));
            }
            return SoundHandle();
        }
        SoundHandle handle;
        if (GfObjUtil::getSePackAll(packs, param.m_obj)) {
            handle = playSeWithPack(param, packs, static_cast<SEINFO>(4));
            if (handle.isValid()) {
                return handle;
            }
        }
        if (manager->getCommonPack() != nullptr) {
            packs.clear();
            packs.push_back(manager->getCommonPack());
            handle = playSeWithPack(param, packs, static_cast<SEINFO>(1));
            if (handle.isValid()) {
                return handle;
            }
        }
        if (GfFieldSound* field = GfFieldSound::get()) {
            if (field->getCommonPack() != nullptr) {
                packs.clear();
                packs.push_back(field->getCommonPack());
                handle = playSeWithPack(param, packs, static_cast<SEINFO>(2));
                if (handle.isValid()) {
                    return handle;
                }
            }
            if (field->getMapPack() != nullptr) {
                packs.clear();
                packs.push_back(field->getMapPack());
                handle = playSeWithPack(param, packs, static_cast<SEINFO>(3));
                if (handle.isValid()) {
                    return handle;
                }
            }
        }
    }
    return SoundHandle();
}

bool GfSound::getSePack(mm::mtl::FixedVector<fw::SoundPack*, 4>& packs, const SoundParam& param) {
    fw::SoundPack* pack;
    switch (param.m_packKind) {
    case 1:
        if (fw::SoundManager* manager = fw::SoundManager::get()) {
            pack = manager->getCommonPack();
            break;
        }
        return !packs.empty();
    case 2:
        if (GfFieldSound* field = GfFieldSound::get()) {
            pack = field->getCommonPack();
            break;
        }
        return !packs.empty();
    case 3:
        if (GfFieldSound* field = GfFieldSound::get()) {
            pack = field->getMapPack();
            break;
        }
        return !packs.empty();
    case 4:
        GfObjUtil::getSePackAll(packs, param.m_obj);
    default:
        return !packs.empty();
    }
    if (pack != nullptr) {
        packs.push_back(pack);
    }
    return !packs.empty();
}

void GfSound::stopSe(SoundHandle handle, float time) {
    if (fw::SoundManager* manager = fw::SoundManager::get()) {
        manager->stopSe(handle.m_id, time);
    }
}

void GfSound::destroyCategorySe(fw::SoundCategory category) {
    if (fw::SoundManager* manager = fw::SoundManager::get()) {
        for (mm::mtl::FixedList<unsigned short, 512>::iterator it = m_seList.begin(); it != m_seList.end(); ++it) {
            if (m_seParams[*it].m_kind == category) {
                manager->stopSe(m_seParams[*it].m_handle.m_id, 0.0f);
            }
        }
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

void GfSound::setPauseForBgmSuspend(SoundHandle handle, bool pause, float time) {
    setPauseType(handle, pause, time, 8);
}

bool GfSound::isPauseForBgmSuspend(SoundHandle handle) const {
    if (const SeParam* param = getSeParam(handle.m_seIndex)) {
        return (param->m_pause >> 3) & 1;
    }
    return false;
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

fw::SoundPack* GfSound::createObjSePack(GfAssetResource* resource) {
    if (resource == nullptr || !resource->isValidData()) {
        return nullptr;
    }
    fw::SoundPack::SetupInfo info;
    info.category = static_cast<fw::SoundCategory>(13);
    info.maxSound = 8;
    info.name = resource->getAssetName();
    info.assetName = resource->getAssetName();
    info.data = resource->getAssetData();
    info.size = resource->getAssetSize();
    return fw::SoundPack::create(info);
}

void GfSound::destroyObjSePack(fw::SoundPack*& pack) {
    if (pack != nullptr) {
        pack->release();
        pack = nullptr;
    }
}
}  // namespace gf

// instantiated for gf::GfSound::updateSeParamList
template mm::mtl::FixedList<unsigned short, 512>::iterator mm::mtl::FixedList<unsigned short, 512>::erase(mm::mtl::FixedList<unsigned short, 512>::iterator);

namespace gf {

void GfSound::setPauseGameSe(bool pause) {
    float volume = pause ? 0.0f : 1.0f;
    setCategoryVolume(m_categoryHandle, static_cast<fw::SoundCategory>(4), volume, 0.0f);
    setCategoryVolume(m_categoryHandle, static_cast<fw::SoundCategory>(5), volume, 0.0f);
    setCategoryVolume(m_categoryHandle, static_cast<fw::SoundCategory>(6), volume, 0.0f);
    setCategoryVolume(m_categoryHandle, static_cast<fw::SoundCategory>(13), volume, 0.0f);
    setCategoryVolume(m_categoryHandle, static_cast<fw::SoundCategory>(14), volume, 0.0f);
    setCategoryVolume(m_categoryHandle, static_cast<fw::SoundCategory>(15), volume, 0.0f);
    setCategoryVolume(m_categoryHandle, static_cast<fw::SoundCategory>(16), volume, 0.0f);
    for (mm::mtl::FixedList<unsigned short, 512>::iterator it = m_seList.begin(); it != m_seList.end(); ++it) {
        SeParam* param = getSeParam(*it);
        bool isTarget = false;
        switch (param->m_kind) {
        case 4:
        case 5:
        case 6:
        case 13:
        case 14:
        case 15:
        case 16:
            isTarget = true;
            break;
        }
        if (isTarget) {
            setPauseType(param->m_handle, pause, 0.0f, 2);
        }
    }
}

void GfSound::setPauseGameWeatherSe(bool pause) {
    float volume = pause ? 0.0f : 1.0f;
    setCategoryVolume(m_categoryHandle, static_cast<fw::SoundCategory>(7), volume, 0.0f);
    setCategoryVolume(m_categoryHandle, static_cast<fw::SoundCategory>(8), volume, 0.0f);
    for (mm::mtl::FixedList<unsigned short, 512>::iterator it = m_seList.begin(); it != m_seList.end(); ++it) {
        SeParam* param = getSeParam(*it);
        switch (param->m_kind) {
        case 7:
        case 8:
            setPauseType(param->m_handle, pause, 0.0f, 2);
            break;
        }
    }
}

void GfSound::setPauseEventSe(bool pause) {
    for (mm::mtl::FixedList<unsigned short, 512>::iterator it = m_seList.begin(); it != m_seList.end(); ++it) {
        SeParam* param = getSeParam(*it);
        bool isTarget = false;
        switch (param->m_kind) {
        case 1:
        case 9:
        case 11:
        case 12:
            isTarget = true;
            break;
        }
        if (isTarget) {
            setPauseType(param->m_handle, pause, 0.0f, 4);
        }
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
