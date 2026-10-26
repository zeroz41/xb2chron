#include "gf/ParamObj.h"
#include "classes/gf/GfGameVoice.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfInfo.h"
#include "classes/gf/GfSound.h"
#include "gf/GfObjUtil.h"
#include "fw/UpdateInfo.h"

namespace gf {

void GfGameVoice::initialize(const GfSetupParam& param) {
    for (int i = 0; i < 6; i++) {
#line 141
        VoiceInfo* info = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) VoiceInfo;
        m_freeList.push_back(info);
    }
    m_isInitialized = true;
}

GfGameVoice::~GfGameVoice() {}

void GfGameVoice::destroy() {
    GfGameVoice* self = sys();
    self->finalize();
    delete self;
}

GAME_VOICE_HANDLE* GfGameVoice::playVoice(GF_OBJ_HANDLE* handle, const char* name, CV_PRIO prio) {
    return playVoice(ParamObj(handle), name, prio, false);
}

GAME_VOICE_HANDLE* GfGameVoice::playVoice(unsigned int type, unsigned int id, const char* name, CV_PRIO prio) {
    return playVoice(ParamObj(type, id), name, prio, false);
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
    m_state = 0;
    m_prio = CV_PRIO(0);
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
