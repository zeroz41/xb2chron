#include "classes/gf/GfFieldSound.h"
#include "classes/gf/GfFieldBgm.h"
#include "classes/gf/GfFieldMapSe.h"
#include "classes/gf/GfSound.h"
#include "classes/gf/GfWeapon.h"
#include "classes/gf/GfFieldSound.h"
#include "classes/gf/GfFieldBgm.h"
#include "classes/gf/GfFieldMapSe.h"
#include "classes/gf/GfSound.h"
#include "classes/gf/GfWeapon.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfInfo.h"
#include "classes/fw/FrameworkMemory.h"
#include "classes/fw/SoundManager.h"
#include "classes/fw/SoundPack.h"
#include "classes/fw/SoundResource.h"
#include "gf/GfDataMap.h"
#include "gf/GfDataSound.h"
#include "gf/GfSetupParam.h"
#include "gf/GfUtil.h"
#include <string.h>

namespace gf {

namespace _gffsn {
// the common SE pack's name (1.0.0's symbol)
const char* s_szCommonName = "se_fld_allmap";
// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100B525B0). The common SE pack's name in
// the DLC game (createCommonSound picks it when s_isDlc is set).
const char* s_szDlcCommonName = "dlc_fld_allmap";
// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100D6C918). GfSetupParam's DLC flag, which
// initialize and createCommonSound store; fn_710027C7D4 and createMapSound pick the DLC pack names by it.
bool s_isDlc;
}  // namespace _gffsn

inline void GfFieldSound::SoundInfo::destroy() {
    m_pack = nullptr;
    if (m_resource != nullptr) {
        m_resource->release();
        m_resource = nullptr;
    }
    m_path.clear();
    m_name.clear();
}

inline void GfFieldSound::SoundInfo::fn_710027CB9C(const char* name) {
    destroy();
    m_path = "sound/se/";
    m_path += name;
    m_path += ".xsp";
    m_name = name;
    fw::SoundResource::SetupInfo info;
    info.pad_8 = 0x80;
    info.pad_0 = 3;
    info.pad_4 = 0;
    m_resource = fw::SoundResource::request(fw::FrameworkMemory::getAllocator(8), m_path.m_str, info,
                                            static_cast<fw::LOAD_PRIO>(10));
    if (m_resource != nullptr) {
        while (!m_resource->valid()) {
            GfSleep(1);
        }
        if (fw::SoundManager* manager = fw::SoundManager::get()) {
            m_pack = manager->findPack(m_name.m_str, nullptr);
        }
    }
}

inline void GfFieldSound::getMapSeFile(mm::mtl::FixStr<128>& path, const char* name) {
    mm::mtl::FixStr<64> file;
    if (_gffsn::s_isDlc) {
        file.format("dlc_%s", name);
    } else {
        file.format("se_fld_%s", name);
    }
    GfDataSound::getFullPath(path, file.m_str);
}

void GfFieldSound::initialize(const GfSetupParam& param) {
    _gffsn::s_isDlc = param.m_dlcCameraParam;
    if (GfSound* sound = GfSound::get()) {
        m_categoryHandle = sound->createCategoryHandle();
        m_mapjumpCategoryHandle = sound->createCategoryHandle();
        m_eventCategoryHandle = sound->createCategoryHandle();
    }
#line 154
    m_bgm = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfFieldBgm;
#line 157
    m_mapSe = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfFieldMapSe;
    createCommonSound(param.m_dlcCameraParam);
    m_isInitialized = true;
}

GfFieldSound::~GfFieldSound() {}

void GfFieldSound::build(const GfSetupParam& param) {
#line 124
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfFieldSound(param);
}

void GfFieldSound::destroy() {
    GfFieldSound* sound = get();
    sound->finalize();
    delete sound;
}

void GfFieldSound::finalize() {
    if (m_mapSe != nullptr) {
        delete m_mapSe;
        m_mapSe = nullptr;
    }
    if (m_bgm != nullptr) {
        delete m_bgm;
        m_bgm = nullptr;
    }
    m_dlcSound.destroy();
    m_commonPack = nullptr;
    m_mapSound.m_pack = nullptr;
    if (m_commonResource != nullptr) {
        m_commonResource->release();
        m_commonResource = nullptr;
    }
    if (m_mapSound.m_resource != nullptr) {
        m_mapSound.m_resource->release();
        m_mapSound.m_resource = nullptr;
    }
    if (GfSound* sound = GfSound::get()) {
        sound->releaseCategoryHandle(m_categoryHandle);
        sound->releaseCategoryHandle(m_mapjumpCategoryHandle);
        sound->releaseCategoryHandle(m_eventCategoryHandle);
    }
    m_isInitialized = false;
}

void GfFieldSound::createCommonSound(bool isDlc) {
    _gffsn::s_isDlc = isDlc;
    const char* name = fn_710027C7D4();
    fw::SoundResource::SetupInfo info;
    info.pad_8 = 0x80;
    info.pad_0 = 5;
    info.pad_4 = 0;
    mm::mtl::FixStr<128> path;
    GfDataSound::getFullPath(path, name);
    m_commonResource = fw::SoundResource::request(fw::FrameworkMemory::getAllocator(8), path.m_str, info,
                                                  static_cast<fw::LOAD_PRIO>(10));
    while (!m_commonResource->valid()) {
        GfSleep(1);
    }
    m_commonPack = fw::SoundManager::get()->findPack(name, nullptr);
}

const char* GfFieldSound::fn_710027C7D4() {
    return _gffsn::s_isDlc ? _gffsn::s_szDlcCommonName : _gffsn::s_szCommonName;
}

void GfFieldSound::destroyCommonSound() {
    m_commonPack = nullptr;
    if (m_commonResource != nullptr) {
        m_commonResource->release();
        m_commonResource = nullptr;
    }
}

void GfFieldSound::update(const fw::UpdateInfo& info) {
    if (m_bgm != nullptr) {
        m_bgm->update(info);
    }
    if (m_mapSe != nullptr) {
        m_mapSe->update(info);
    }
}

void GfFieldSound::postUpdate(const fw::UpdateInfo& info) {
    if (m_mapSe != nullptr) {
        m_mapSe->postUpdate(info);
    }
}

void GfFieldSound::clear() {
    if (m_bgm != nullptr) {
        m_bgm->destroy();
    }
    if (m_mapSe != nullptr) {
        m_mapSe->destroy();
    }
}

void GfFieldSound::gevGameMapModel(GF_OBJ_HANDLE* handle, bool flag) {
    if (m_mapSe != nullptr) {
        m_mapSe->gevGameMapModel(handle, flag);
    }
}

void GfFieldSound::gevPlayEvent(GEV gev, unsigned int eventId) {
    if (m_bgm != nullptr) {
        m_bgm->gevPlayEvent(gev, eventId);
    }
}

void GfFieldSound::gevBattleEnd() {
    if (m_bgm != nullptr) {
        m_bgm->gevBattleEnd();
    }
}

void GfFieldSound::gevMapjump(GEV gev, const MapjumpCallbackInfo& info) {
    if (GfFieldBgm* bgm = GfFieldBgm::get()) {
        bgm->gevMapjump(gev, info);
    }
}

void GfFieldSound::gevPause(unsigned int flags0, unsigned int flags1) {
    if (m_bgm != nullptr) {
        m_bgm->gevPause(flags0, flags1);
    }
    if (m_mapSe != nullptr) {
        m_mapSe->gevPause(flags0, flags1);
    }
}

void GfFieldSound::createMapSound() {
    destroyMapSound();
    if (const char* resourceName = GfDataMap::getMapResourceName(GfGameManager::getMapJumpID())) {
        fw::SoundResource::SetupInfo info;
        info.pad_8 = 0x80;
        info.pad_0 = 5;
        info.pad_4 = 0;
        getMapSeFile(m_mapSound.m_path, resourceName);
        m_mapSound.m_name = util::getNoPathExtName(m_mapSound.m_path.m_str);
        m_mapSound.m_resource = fw::SoundResource::request(fw::FrameworkMemory::getAllocator(8),
                                                           m_mapSound.m_path.m_str, info,
                                                           static_cast<fw::LOAD_PRIO>(10));
    }
    if (fn_71002ED330()) {
        m_dlcSound.fn_710027CB9C("dlc_se_btl_spskill");
    }
}

void GfFieldSound::destroyMapSound() {
    m_dlcSound.destroy();
    m_mapSound.destroy();
}

void GfFieldSound::waitLoadMapSound() {
    if (m_mapSound.m_resource != nullptr) {
        while (!m_mapSound.m_resource->valid()) {
            GfSleep(1);
        }
        if (fw::SoundManager* manager = fw::SoundManager::get()) {
            m_mapSound.m_pack = manager->findPack(m_mapSound.m_name.m_str, nullptr);
        }
    }
    while (m_dlcSound.m_resource != nullptr && m_dlcSound.m_pack == nullptr) {
        GfSleep(1);
    }
}

fw::SoundPack* GfFieldSound::getCommonPack() {
    return m_commonPack;
}

fw::SoundPack* GfFieldSound::getMapPack() {
    return m_mapSound.m_pack;
}

fw::SoundPack* GfFieldSound::fn_710027CE60(const char* name) {
    fw::SoundPack* pack = m_dlcSound.m_pack;
    if (pack != nullptr && !pack->findSource(name)) {
        pack = nullptr;
    }
    return pack;
}

const char* GfFieldSound::fn_710027CEA4(const char* name) {
    if (strcmp(name, "btl_spskill_001") == 0) {
        return "dlc_se_btl_bl40040116";
    }
    if (strcmp(name, "btl_spskill_002") == 0) {
        return "dlc_se_btl_bl40040117";
    }
    if (strcmp(name, "btl_spskill_003") == 0) {
        return "dlc_se_btl_bl40040118";
    }
    if (strcmp(name, "btl_spskill_004") == 0) {
        return "dlc_se_btl_bl40040119";
    }
    return nullptr;
}

void GfFieldSound::setCategorySeFadeoutForMapjump(float time) {
    if (GfSound* sound = GfSound::get()) {
        sound->setCategoryVolume(m_mapjumpCategoryHandle, static_cast<fw::SoundCategory>(2), 0.0f, time);
        sound->setCategoryVolume(m_mapjumpCategoryHandle, static_cast<fw::SoundCategory>(4), 0.0f, time);
        sound->setCategoryVolume(m_mapjumpCategoryHandle, static_cast<fw::SoundCategory>(5), 0.0f, time);
        sound->setCategoryVolume(m_mapjumpCategoryHandle, static_cast<fw::SoundCategory>(6), 0.0f, time);
        sound->setCategoryVolume(m_mapjumpCategoryHandle, static_cast<fw::SoundCategory>(7), 0.0f, time);
        sound->setCategoryVolume(m_mapjumpCategoryHandle, static_cast<fw::SoundCategory>(13), 0.0f, time);
        sound->setCategoryVolume(m_mapjumpCategoryHandle, static_cast<fw::SoundCategory>(14), 0.0f, time);
        sound->setCategoryVolume(m_mapjumpCategoryHandle, static_cast<fw::SoundCategory>(15), 0.0f, time);
        sound->setCategoryVolume(m_mapjumpCategoryHandle, static_cast<fw::SoundCategory>(16), 0.0f, time);
    }
}

void GfFieldSound::setCategorySeFadeinForMapjump(float time) {
    if (GfSound* sound = GfSound::get()) {
        sound->setCategoryVolume(m_mapjumpCategoryHandle, static_cast<fw::SoundCategory>(2), 1.0f, time);
        sound->setCategoryVolume(m_mapjumpCategoryHandle, static_cast<fw::SoundCategory>(4), 1.0f, time);
        sound->setCategoryVolume(m_mapjumpCategoryHandle, static_cast<fw::SoundCategory>(5), 1.0f, time);
        sound->setCategoryVolume(m_mapjumpCategoryHandle, static_cast<fw::SoundCategory>(6), 1.0f, time);
        sound->setCategoryVolume(m_mapjumpCategoryHandle, static_cast<fw::SoundCategory>(7), 1.0f, time);
        sound->setCategoryVolume(m_mapjumpCategoryHandle, static_cast<fw::SoundCategory>(13), 1.0f, time);
        sound->setCategoryVolume(m_mapjumpCategoryHandle, static_cast<fw::SoundCategory>(14), 1.0f, time);
        sound->setCategoryVolume(m_mapjumpCategoryHandle, static_cast<fw::SoundCategory>(15), 1.0f, time);
        sound->setCategoryVolume(m_mapjumpCategoryHandle, static_cast<fw::SoundCategory>(16), 1.0f, time);
    }
}

void GfFieldSound::destroyCategorySeForMapjump() {
    if (GfSound* sound = GfSound::get()) {
        sound->destroyCategorySe(static_cast<fw::SoundCategory>(5));
        sound->destroyCategorySe(static_cast<fw::SoundCategory>(6));
        sound->destroyCategorySe(static_cast<fw::SoundCategory>(7));
        sound->destroyCategorySe(static_cast<fw::SoundCategory>(13));
        sound->destroyCategorySe(static_cast<fw::SoundCategory>(14));
        sound->destroyCategorySe(static_cast<fw::SoundCategory>(15));
        sound->destroyCategorySe(static_cast<fw::SoundCategory>(16));
    }
}

}  // namespace gf
