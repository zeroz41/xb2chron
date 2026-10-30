#include "gf/ParamObj.h"
#include "classes/gf/GfGameVoice.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfInfo.h"
#include "classes/gf/GfSound.h"
#include "gf/GfObjUtil.h"
#include "fw/UpdateInfo.h"
#include "fw/LangUtil.h"
#include "classes/gf/DataParamAcc.h"
#include "mm/mtl/FixStr.h"

namespace gf {
namespace _gfgvo {
// the voice files' folder and extension (PJOB_PLAY::exec, playVoice(const char*), playNarrationVoice)
const char* s_szVoicePath = "/stream/voice/";
const char* s_szVoiceExt = ".wav";
}  // namespace _gfgvo


void GfGameVoice::initialize(const GfSetupParam& param) {
    for (int i = 0; i < 6; i++) {
#line 141
        VoiceInfo* info = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) VoiceInfo;
        m_freeList.push_back(info);
    }
    m_isInitialized = true;
}

GfGameVoice::~GfGameVoice() {}

void GfGameVoice::build(const GfSetupParam& param) {
#line 122
    GfGameVoice* self = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfGameVoice;
    self->initialize(param);
}

void GfGameVoice::destroy() {
    GfGameVoice* self = sys();
    self->finalize();
    delete self;
}

void GfGameVoice::finalize() {
    while (m_freeList.size() != 6) {
        GfSleep(1);
    }
    for (mm::mtl::FixedList<VoiceInfo*, 6>::iterator it = m_freeList.begin(); it != m_freeList.end(); ++it) {
        delete *it;
    }
    m_freeList.clear();
    m_isInitialized = false;
}

void GfGameVoice::update(const fw::UpdateInfo& info) {
    GfGameVoice* self = sys();
    if (self == nullptr) {
        return;
    }
    typedef mm::mtl::FixedList<VoiceInfo*, 6>::iterator iterator;
    for (iterator it = self->m_playList.begin(); it != self->m_playList.end(); ++it) {
        (*it)->checkInvalid(info);
    }
    for (iterator it = self->m_playList.begin(); it != self->m_playList.end();) {
        VoiceInfo*& voice = *it;
        if (voice->isEmpty()) {
            self->m_freeList.push_back(voice);
            it = self->m_playList.erase(it);
        } else {
            ++it;
        }
    }
    for (iterator it = self->m_playList.begin(); it != self->m_playList.end(); ++it) {
        (*it)->update(info);
    }
}

inline void VoiceInfo::addStop(CV_PRIO prio) {
    if (!m_jobs.full() && m_sound.isValid()) {
#line 921
        m_jobs.push_back(new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) PJOB_STOP(this, prio));
    }
}

GAME_VOICE_HANDLE* GfGameVoice::playVoice(GF_OBJ_HANDLE* handle, const char* name, CV_PRIO prio) {
    return playVoice(ParamObj(handle), name, prio, false);
}

GAME_VOICE_HANDLE* GfGameVoice::playVoice(unsigned int type, unsigned int id, const char* name, CV_PRIO prio) {
    return playVoice(ParamObj(type, id), name, prio, false);
}

void GfGameVoice::playStop(GAME_VOICE_HANDLE* voice) {
    GfGameVoice* self = get();
    if (self == nullptr) {
        return;
    }
    for (mm::mtl::FixedList<VoiceInfo*, 6>::iterator it = self->m_playList.begin(); it != self->m_playList.end();
         ++it) {
        VoiceInfo* info = *it;
        if (info->m_voice == voice) {
            if (info != nullptr) {
                info->addStop(CV_PRIO(0));
            }
            return;
        }
    }
}

void GfGameVoice::gevLayerPause(unsigned int layer, bool pause) {
    GfGameVoice* self = sys();
    for (mm::mtl::FixedList<VoiceInfo*, 6>::iterator it = self->m_playList.begin(); it != self->m_playList.end();
         ++it) {
        if (GfObjUtil::getObjLayer((*it)->m_obj.m_handle) == layer) {
        }
    }
}

void GfGameVoice::gevMapjump(GEV gev, const MapjumpCallbackInfo& info) {
    if (gev == GEV(2)) {
        destroyVoiceAll();
    }
}

bool GfGameVoice::isPlayVoice(GF_OBJ_HANDLE* handle) const {
    GfGameVoice* self = const_cast<GfGameVoice*>(this);
    ParamObj obj(handle);
    for (mm::mtl::FixedList<VoiceInfo*, 6>::iterator it = self->m_playList.begin(); it != self->m_playList.end();
         ++it) {
        if ((*it)->m_obj == obj) {
            return true;
        }
    }
    return false;
}

void VoiceInfo::clear() {
    if (m_sound.isValid()) {
        if (GfSound::get() != nullptr) {
            GfSound::get()->stopVoice(m_sound, 0.0f);
        }
        m_sound.clear();
    }
    m_prio = CV_PRIO(0);
    m_state = 0;
    m_voice = nullptr;
    m_time = 0.0f;
    m_obj = ParamObj(0, 0);
    m_waitForOthers = false;
    // the original never advances the iterator: it deletes the first job until the queue's end moves onto it
    for (mm::mtl::FixedQueue<PJOB*, 16>::iterator it = m_jobs.begin(); it != m_jobs.end();) {
        delete *it;
    }
    m_jobs.clear();
    m_isFree = true;
}

bool VoiceInfo::PJOB_PLAY::exec() {
    GfSound* sound = GfSound::get();
    if (sound != nullptr) {
        if (m_info->m_waitForOthers) {
            GfGameVoice* self = GfGameVoice::sys();
            for (mm::mtl::FixedList<VoiceInfo*, 6>::iterator it = self->m_playList.begin();
                 it != self->m_playList.end(); ++it) {
                // the original asks GfObjUtil for an object's type when the slot has none and ignores the answer
                unsigned int type = (*it)->m_obj.m_type;
                if (type == 0) {
                    GfObjUtil::getObjType((*it)->m_obj.m_handle);
                    type = (*it)->m_obj.m_type;
                }
                if (type == 3 || type == 4) {
                    SoundHandle playing = (*it)->m_sound;
                    if (playing.isValid()) {
                        return false;
                    }
                }
            }
        }
        DataParamAcc acc(m_obj);
        fw::SoundCategory category = acc.getObjType() == 5 ? fw::SoundCategory(15) : fw::SoundCategory(2);
        const char* folder = fw::LangUtil::getVoiceFolder();
        mm::mtl::FixStr<16> path;
        {
            GfVoiceName name(m_name.m_name.m_str);
            name.getVoicePath(path);
        }
        mm::mtl::FixStr<128> file;
        file.format("%s%s/%s%s%s", _gfgvo::s_szVoicePath, folder, path.m_str, m_name.m_name.m_str,
                    _gfgvo::s_szVoiceExt);
        SoundHandle handle = sound->playVoice(file.m_str, 1.0f, false, category);
        m_info->setPlayInfoStart(m_voice, handle, m_obj, m_prio);
    }
    return true;
}

bool VoiceInfo::PJOB_STOP::exec() {
    GfSound* sound = GfSound::get();
    if (sound != nullptr && m_info->m_sound.isValid()) {
        sound->stopVoice(m_info->m_sound, 0.0f);
        m_info->setPlayInfoStop(m_prio);
    }
    return true;
}

bool VoiceInfo::PJOB_WAIT_STOP::exec() {
    return !m_info->m_sound.isValid();
}

}  // namespace gf
