#include "mm/mtl/FixedVector.h"
#include "gf/SoundHandle.h"
#include "classes/gf/GfSound.h"
#include "classes/gf/GfBdatBgm.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/GfMenuSoundManager.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfDataBdat.h"
#include "mm/mtl/FixStr.h"
#include "plugin/Bdat.h"
#include "string.h"

namespace gf {

namespace {
// the BDAT table of jingles: a row's "resource" (a BGM list row) and "time" (how long it plays)
const unsigned int JINGLE_BDAT = 0x188;  // the name is not the original's

// the jingles that leave the field BGM as it is (playJingle does not turn it down for them, and postUpdate does not
// turn it back up after them); the name is not the original's
bool keepsFieldBgm(unsigned int id) {
    switch (id) {
    case 12:
    case 13:
    case 18:
        return true;
    default:
        return false;
    }
}
}  // namespace

GfMenuSoundManager::~GfMenuSoundManager() {}

void GfMenuSoundManager::build(const GfSetupParam& param) {
#line 39
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfMenuSoundManager();
}

void GfMenuSoundManager::destroy() {
    GfMenuSoundManager* manager = get();
    manager->m_initialized = false;
    if (GfSound* sound = GfSound::get()) {
        sound->releaseCategoryHandle(manager->m_categoryHandle);
    }
    delete manager;
}

bool GfMenuSoundManager::isInitialized() {
    GfMenuSoundManager* manager = get();
    return manager != nullptr && manager->m_initialized;
}

void GfMenuSoundManager::postUpdate(const fw::UpdateInfo& info) {
    GfMenuSoundManager* manager = get();
    if (manager == nullptr) {
        return;
    }
    GfSound* sound = GfSound::get();
    if (sound == nullptr) {
        return;
    }
    unsigned char* fp = GfDataBdat::getFP(JINGLE_BDAT);
    for (JingleInfo* it = manager->m_jingles.begin(); it != manager->m_jingles.end();) {
        // a float column: its value is the low 32 bits of what getVal returns
        unsigned int timeBits = static_cast<unsigned int>(reinterpret_cast<unsigned long>(Bdat::getVal(fp, "time", it->m_id)));
        float time;
        memcpy(&time, &timeBits, sizeof(time));
        float playTime = 0.0f;
        sound->getPlayTime(it->m_handle, playTime);
        if (playTime > time || !sound->isPlaying(it->m_handle)) {
            unsigned int id = it->m_id;
            manager->m_jingles.erase(it);
            if (manager->m_jingles.size() == 0 && !keepsFieldBgm(id) && !GfMenuManager::isOpenFullScreen()) {
                fadeInFieldBgm(1.0f);
            }
        } else {
            ++it;
        }
    }
}

void GfMenuSoundManager::fadeInFieldBgm(float time) {
    GfMenuSoundManager* manager = get();
    if (manager == nullptr) {
        return;
    }
    if (GfSound* sound = GfSound::get()) {
        sound->setCategoryVolume(manager->m_categoryHandle, fw::SoundCategory(1), 1.0f, time);
        sound->setCategoryVolume(manager->m_categoryHandle, fw::SoundCategory(7), 1.0f, time);
        sound->setCategoryVolume(manager->m_categoryHandle, fw::SoundCategory(8), 1.0f, time);
    }
}

SoundHandle GfMenuSoundManager::playJingle(unsigned int id) {
    GfMenuSoundManager* manager = get();
    if (manager == nullptr || manager->m_jingles.size() == manager->m_jingles.capacity()) {
        return SoundHandle(0);
    }
    GfSound* sound = GfSound::get();
    if (sound == nullptr) {
        return SoundHandle(0);
    }
    unsigned char* fp = GfDataBdat::getFP(JINGLE_BDAT);
    unsigned short resource = static_cast<unsigned short>(reinterpret_cast<unsigned long>(Bdat::getVal(fp, "resource", id)));
    const char* name;
    if (resource == 0 || (name = GfBdatBgm::get()->getBgmListfilename(resource)) == nullptr || name[0] == '\0') {
        return SoundHandle(0);
    }
    mm::mtl::FixStr<128> path;
    path.format("stream/bgm/%s", name);
    SoundHandle handle = sound->playVoice(path.m_str, 1.0f, false, fw::SoundCategory(3));
    if (manager->m_jingles.size() == 0 && !keepsFieldBgm(id) && !GfMenuManager::isOpenFullScreen()) {
        fadeFieldBgm(0.5f, 0.5f);
    }
    JingleInfo jingle;
    jingle.m_handle = handle;
    jingle.m_id = id;
    manager->m_jingles.push_back(jingle);
    return handle;
}

void GfMenuSoundManager::fadeFieldBgm(float time, float volume) {
    GfMenuSoundManager* manager = get();
    if (manager == nullptr) {
        return;
    }
    if (GfSound* sound = GfSound::get()) {
        sound->setCategoryVolume(manager->m_categoryHandle, fw::SoundCategory(1), volume, time);
        sound->setCategoryVolume(manager->m_categoryHandle, fw::SoundCategory(7), volume, time);
        sound->setCategoryVolume(manager->m_categoryHandle, fw::SoundCategory(8), volume, time);
    }
}

void GfMenuSoundManager::fadeOutFieldBgm(float time) {
    GfMenuSoundManager* manager = get();
    if (manager == nullptr) {
        return;
    }
    if (GfSound* sound = GfSound::get()) {
        sound->setCategoryVolume(manager->m_categoryHandle, fw::SoundCategory(1), 0.0f, time);
        sound->setCategoryVolume(manager->m_categoryHandle, fw::SoundCategory(7), 0.0f, time);
        sound->setCategoryVolume(manager->m_categoryHandle, fw::SoundCategory(8), 0.0f, time);
    }
}

}  // namespace gf
