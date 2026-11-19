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
#include "classes/gf/GfReqSmallCom.h"
#include "classes/gf/SCOM_FIELD_VOICE.h"
#include "classes/gf/GfBdatBtl.h"
#include "classes/gf/GfGameCond.h"
#include "classes/gf/GfGameManager.h"
#include "gf/GfDataBlade.h"
#include "gf/GfDataDriver.h"
#include "gf/GfFieldVoice.h"
#include "gf/GfSalvageVoice.h"
#include "ml/MTRand.h"
#include "mm/mtl/FixedArray.h"

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

void VoiceInfo::addPlay(GAME_VOICE_HANDLE* voice, const ParamObj& obj, const GfVoiceName& name, CV_PRIO prio) {
    if (!m_jobs.full()) {
        m_obj = obj;
#line 894
        m_jobs.push_back(new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8)
                             PJOB_PLAY(this, voice, obj, name, prio));
    }
}

GAME_VOICE_HANDLE* GfGameVoice::playNarrationVoice(const char* name) {
    GfVoiceName voiceName(name);
    GfSound* sound = GfSound::get();
    if (sound != nullptr) {
        const char* folder = fw::LangUtil::getVoiceFolder();
        mm::mtl::FixStr<16> path;
        {
            GfVoiceName pathName(voiceName.m_name.m_str);
            pathName.getVoicePath(path);
        }
        mm::mtl::FixStr<128> file;
        file.format("%s%s/%s%s%s", _gfgvo::s_szVoicePath, folder, path.m_str, voiceName.m_name.m_str,
                    _gfgvo::s_szVoiceExt);
        GfGameVoice* self = get();
        if (self != nullptr && !self->m_freeList.empty()) {
            GAME_VOICE_HANDLE* voice = self->createHandle();
            VoiceInfo* info = self->m_freeList.front();
            self->m_freeList.pop_front();
            self->m_playList.push_back(info);
            SoundHandle handle = sound->playVoice(file.m_str, 1.0f, false, fw::SoundCategory(16));
            info->m_obj = ParamObj(3, 0xffff);
            info->m_prio = CV_PRIO(5);
            info->m_sound = handle;
            info->m_voice = voice;
            return voice;
        }
    }
    return nullptr;
}

GAME_VOICE_HANDLE* GfGameVoice::playVoice(const char* name) {
    GfVoiceName voiceName(name);
    GfSound* sound = GfSound::get();
    if (sound != nullptr) {
        const char* folder = fw::LangUtil::getVoiceFolder();
        mm::mtl::FixStr<16> path;
        {
            GfVoiceName pathName(voiceName.m_name.m_str);
            pathName.getVoicePath(path);
        }
        mm::mtl::FixStr<128> file;
        file.format("%s%s/%s%s%s", _gfgvo::s_szVoicePath, folder, path.m_str, voiceName.m_name.m_str,
                    _gfgvo::s_szVoiceExt);
        GfGameVoice* self = get();
        if (self != nullptr && !self->m_freeList.empty()) {
            GAME_VOICE_HANDLE* voice = self->createHandle();
            VoiceInfo* info = self->m_freeList.front();
            self->m_freeList.pop_front();
            self->m_playList.push_back(info);
            SoundHandle handle = sound->playVoice(file.m_str, 1.0f, false, fw::SoundCategory(2));
            info->m_obj = ParamObj(3, 0xfffe);
            info->m_prio = CV_PRIO(3);
            info->m_sound = handle;
            info->m_voice = voice;
            return voice;
        }
    }
    return nullptr;
}

GAME_VOICE_HANDLE* GfGameVoice::playVoice(GF_OBJ_HANDLE* handle, const char* name, CV_PRIO prio) {
    return playVoice(ParamObj(handle), name, prio, false);
}

GAME_VOICE_HANDLE* GfGameVoice::playVoice(unsigned int type, unsigned int id, const char* name, CV_PRIO prio) {
    return playVoice(ParamObj(type, id), name, prio, false);
}

GAME_VOICE_HANDLE* GfGameVoice::playVoiceParty(unsigned int type, unsigned int id, const char* name, CV_PRIO prio) {
    return playVoice(ParamObj(type, id), name, prio, true);
}

GAME_VOICE_HANDLE* GfGameVoice::playVoiceParty(GF_OBJ_HANDLE* handle, const char* name, CV_PRIO prio) {
    GAME_VOICE_HANDLE* voice = playVoice(ParamObj(handle), name, prio, false);
    if (voice != nullptr) {
        GfGameVoice* self = sys();
        for (mm::mtl::FixedList<VoiceInfo*, 6>::iterator it = self->m_playList.begin();
             it != self->m_playList.end(); ++it) {
            VoiceInfo* info = *it;
            if (info->m_voice == voice) {
                if (info != nullptr) {
                    info->m_waitForOthers = true;
                }
                return voice;
            }
        }
    }
    return voice;
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

void GfGameVoice::playStop(GF_SCOM_HANDLE* voice) {
    SCOM_FIELD_VOICE::playStop(voice);
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

bool GfVoiceName::getVoicePath(mm::mtl::FixStr<16>& path) const {
    if (!isValid()) {
        return false;
    }
    path = m_name.substr(0, m_number);
    path += "/";
    return true;
}

bool GfGameVoice::isPlayEnemyVoice() const {
    GfGameVoice* self = const_cast<GfGameVoice*>(this);
    for (mm::mtl::FixedList<VoiceInfo*, 6>::iterator it = self->m_playList.begin(); it != self->m_playList.end();
         ++it) {
        if ((*it)->getName().isEnemyVoice()) {
            return true;
        }
    }
    return false;
}

const GfVoiceName& VoiceInfo::getName() const {
    static GfVoiceName s_none("");
    typedef mm::mtl::FixedQueue<PJOB*, 16>::const_iterator iterator;
    for (iterator it = m_jobs.begin(), end = m_jobs.end(); it != end; ++it) {
        if (const GfVoiceName* name = (*it)->getName()) {
            return *name;
        }
    }
    return s_none;
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

namespace _gfgvo {
// Proposed names, not the original's: the symbols leave them unnamed (lbl_71009BBE9C, lbl_71009BBEA8). A salvage
// voice's first and last number by CV_SALVAGE (the middle one is always 01). Fixed arrays, not plain ones: playVoice
// keeps its `n < 10` test on a loaded group (InstCombine folds compares on loads from a plain constant array, and
// every group is 50 or 60), and each table is addressed from its own base.
const mm::mtl::FixedArray<unsigned char, 12> s_salvageVoiceGroup = {{60, 60, 60, 60, 60, 50, 60, 60, 60, 60, 60, 60}};
const mm::mtl::FixedArray<unsigned char, 12> s_salvageVoiceNo = {{1, 2, 3, 4, 5, 1, 6, 7, 8, 9, 10, 11}};
}  // namespace _gfgvo

GAME_VOICE_HANDLE* GfSalvageVoice::playVoice(GF_OBJ_HANDLE* handle, CV_SALVAGE voice) {
    DataParamAcc acc(handle);
    if (acc.getObjType() == 3 && acc.isValid() && acc.getObjType() == 3 && acc.getBdatId() == 1) {
        unsigned int group = _gfgvo::s_salvageVoiceGroup[voice];
        unsigned int no = _gfgvo::s_salvageVoiceNo[voice];
        mm::mtl::FixStr<16> name;
        name = acc.getVoiceStr();
        GfVoiceName::addNumber2keta(name, group);
        GfVoiceName::addNumber2keta(name, 1);
        GfVoiceName::addNumber2keta(name, no);
        return GfGameVoice::playVoice(ParamObj(handle), name.m_str, CV_PRIO(1), false);
    }
    return nullptr;
}

GAME_VOICE_HANDLE* GfSalvageVoice::playResultVoice(GF_OBJ_HANDLE* handle, CV_SALVAGE_RESULT voice) {
    DataParamAcc acc(handle);
    if (acc.getObjType() == 3 && acc.isValid() && acc.getObjType() == 3 && acc.getBdatId() == 1) {
        mm::mtl::FixStr<16> name;
        name = acc.getVoiceStr();
        GfVoiceName::addNumber2keta(name, 60);
        GfVoiceName::addNumber2keta(name, 1);
        GfVoiceName::addNumber2keta(name, voice + 12);
        return GfGameVoice::playVoice(ParamObj(handle), name.m_str, CV_PRIO(1), false);
    }
    return nullptr;
}

namespace _gfgvo {
// Proposed names, not the original's: the symbols leave them unnamed (lbl_71009BBF02, lbl_71009BBF50). The first
// number of a driver's and of a blade's field voice, by CV_FIELD.
const mm::mtl::FixedArray<unsigned char, 39> s_fieldDriverVoiceGroup = {{50, 51, 52, 53, 54, 55, 57, 59, 1, 62, 64, 65, 66, 66, 66, 68, 70, 72, 73, 77, 78, 80, 82, 2, 2, 84, 85, 87, 88, 88, 95, 96, 96, 98, 98, 98, 65, 94, 95}};
const mm::mtl::FixedArray<unsigned char, 39> s_fieldBladeVoiceGroup = {{50, 51, 52, 53, 54, 56, 58, 59, 1, 61, 63, 65, 66, 66, 66, 67, 69, 71, 73, 79, 79, 81, 83, 2, 2, 84, 85, 86, 88, 88, 94, 97, 97, 98, 98, 98, 65, 94, 95}};
}  // namespace _gfgvo

GAME_VOICE_HANDLE* GfFieldVoice::playVoice(const ParamObj& obj, CV_FIELD field, unsigned int no, unsigned int take,
                                           CV_PRIO prio) {
    DataParamAcc acc(obj);
    if (acc.getObjType() != 3 && acc.getObjType() != 4) {
        return nullptr;
    }
    const mm::mtl::FixedArray<unsigned char, 39>& groups =
        acc.getObjType() == 3 ? _gfgvo::s_fieldDriverVoiceGroup : _gfgvo::s_fieldBladeVoiceGroup;
    unsigned int group = groups[field];
    mm::mtl::FixStr<16> name;
    name = acc.getVoiceStr();
    GfVoiceName::addNumber2keta(name, group);
    GfVoiceName::addNumber2keta(name, no + 1);
    GfVoiceName::addNumber2keta(name, take + 1);
    if (strcmp(acc.getVoiceStr(), "15") == 0) {
        name += "a";
    }
    unsigned int id;
    if (acc.getObjType() == 3) {
        id = acc.isValid() && acc.getObjType() == 3 ? acc.getBdatId() : 0;
    } else {
        id = acc.isValid() ? acc.getBdatId() : 0;
    }
    return GfGameVoice::playVoice(ParamObj(acc.getObjType(), id), name.m_str, prio, false);
}

}  // namespace gf
