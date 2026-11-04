#ifndef CLASSES_GF_GFGAMEVOICE_H
#define CLASSES_GF_GFGAMEVOICE_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/FixedList.h"
#include "mm/mtl/FixedQueue.h"
#include "mm/mtl/FixStr.h"
#include "gf/ParamObj.h"
#include "gf/SoundHandle.h"

namespace fw { class UpdateInfo; }
namespace gf { class GfGameVoice; class GfSetupParam; class GAME_VOICE_HANDLE; class GF_OBJ_HANDLE; class GF_SCOM_HANDLE; enum CV_RESULT : int; }
namespace gf { enum GEV : int; class MapjumpCallbackInfo; class QuestCompleteParam; class QuestCompleteChildParam; }
namespace gf { enum CV_PRIO : int; }

namespace gf {
// a voice's name as GfGameVoice plays it: the name and two numbers its constructor reads from it (the voice
// path's parts, see getVoicePath). The member names are not the original's.
class GfVoiceName {
public:
    GfVoiceName(const char* name);
    // user-declared: PJOB_PLAY's slot 0 is its own empty destructor (a member with a non-trivial destructor), not
    // PJOB's as in PJOB_STOP's and PJOB_WAIT_STOP's tables
    ~GfVoiceName() {}
    void getVoicePath(mm::mtl::FixStr<16>& path) const;

    mm::mtl::FixStr<16> m_name;
    int m_kind;
    int m_number;
};

// one voice slot of GfGameVoice (200 bytes; GfGameVoice::initialize makes six): the voice it plays and a queue of
// jobs (play, stop, wait) its update runs in order. The member names are not the original's.
class VoiceInfo {
public:
    // a queued job: exec returns true when it is done (VoiceInfo::update then deletes it and runs the next)
    // table none (its derived classes')
    class PJOB {
    public:
        PJOB(VoiceInfo* info) : m_info(info) {}
        virtual ~PJOB() {}  // slot 0
        virtual bool exec() = 0;  // slot 2
        virtual const char* getName() { return nullptr; }  // slot 3
        virtual GAME_VOICE_HANDLE* getVoiceHandle() const { return nullptr; }  // slot 4

        VoiceInfo* m_info;
    };
    // table 0x7100B56B60
    class PJOB_PLAY : public PJOB {
    public:
        PJOB_PLAY(VoiceInfo* info, GAME_VOICE_HANDLE* voice, const ParamObj& obj, const GfVoiceName& name,
                  CV_PRIO prio)
            : PJOB(info), m_voice(voice), m_obj(obj), m_name(name), m_prio(prio) {}
        virtual ~PJOB_PLAY() {}  // slot 0
        virtual bool exec();  // slot 2
        virtual const char* getName() { return m_name.m_name.m_str; }  // slot 3
        virtual GAME_VOICE_HANDLE* getVoiceHandle() const { return m_voice; }  // slot 4

        GAME_VOICE_HANDLE* m_voice;
        ParamObj m_obj;
        GfVoiceName m_name;
        CV_PRIO m_prio;
    };
    // table 0x7100B56B98
    class PJOB_STOP : public PJOB {
    public:
        PJOB_STOP(VoiceInfo* info, CV_PRIO prio) : PJOB(info), m_prio(prio) {}
        virtual bool exec();  // slot 2

        CV_PRIO m_prio;
    };
    // table 0x7100B56BD0
    class PJOB_WAIT_STOP : public PJOB {
    public:
        PJOB_WAIT_STOP(VoiceInfo* info) : PJOB(info) {}
        virtual bool exec();  // slot 2
    };

    VoiceInfo()
        : m_isFree(true), m_prio(CV_PRIO(0)), m_time(0.0f), m_obj(0, 0), m_voice(nullptr), m_waitForOthers(false) {
        clear();
    }

    void clear();
    void checkInvalid(const fw::UpdateInfo& info);
    void update(const fw::UpdateInfo& info);
    void addPlay(GAME_VOICE_HANDLE* voice, const ParamObj& obj, const GfVoiceName& name, CV_PRIO prio);
    void setPlayInfoStart(GAME_VOICE_HANDLE* voice, SoundHandle sound, const ParamObj& obj, CV_PRIO prio);
    void setPlayInfoStop(CV_PRIO prio);
    // queues a stop unless the queue is full or nothing plays (GfGameVoice::destroyVoiceAll; the name is not the
    // original's)
    inline void addStop(CV_PRIO prio);
    // the slot plays voice or has a job for it (1.0.0's gf::VoiceInfo::isEnableVoiceHandle(GAME_VOICE_HANDLE*) const,
    // 0x710035ADAC; 3.0.1 inlines it into getResult)
    bool isEnableVoiceHandle(GAME_VOICE_HANDLE* voice) const {
        if (voice == nullptr) {
            return false;
        }
        if (m_voice == voice) {
            return true;
        }
        for (mm::mtl::FixedQueue<PJOB*, 16>::const_iterator it = m_jobs.begin(); it != m_jobs.end(); ++it) {
            if ((*it)->getVoiceHandle() == voice) {
                return true;
            }
        }
        return false;
    }
    // nothing plays and no job is queued (1.0.0's gf::VoiceInfo::isEmpty() const, 0x7100358E44; 3.0.1 inlines it)
    bool isEmpty() const { return !m_sound.isValid() && m_jobs.empty(); }

    bool m_isFree;  // clear sets it
    CV_PRIO m_prio;  // the playing voice's (setPlayInfoStart sets it, setPlayInfoStop compares and clears it)
    int m_state;
    float m_time;  // seconds the voice has played (update); checkInvalid gives up past 60
    ParamObj m_obj;
    SoundHandle m_sound;
    GAME_VOICE_HANDLE* m_voice;
    // PJOB_PLAY::exec holds the voice while an object of type 3 or 4 has a voice playing
    bool m_waitForOthers;
    mm::mtl::FixedQueue<PJOB*, 16> m_jobs;
};

// table 0x7100B56B40
class GfGameVoice : public ::mm::mtl::PtrSingleton< ::gf::GfGameVoice> {
public:
    // how a voice ended, kept for getResult (the names are not the original's)
    struct Result {
        Result(const ParamObj& obj, GAME_VOICE_HANDLE* voice, CV_RESULT result)
            : m_obj(obj), m_voice(voice), m_result(result) {}

        ParamObj m_obj;
        GAME_VOICE_HANDLE* m_voice;
        CV_RESULT m_result;
    };

    GfGameVoice() : m_isInitialized(false), m_voiceCount(0) {}
    virtual ~GfGameVoice();  // slot 0

    static void build(const GfSetupParam& param);
    static void destroy();
    void initialize(const GfSetupParam& param);
    void finalize();
    static void update(const fw::UpdateInfo& info);
    static void destroyVoiceAll();
    static void gevLayerPause(unsigned int layer, bool pause);
    // SCOM_FIELD_VOICE::exec stops a voice it cuts short, then asks how it ended
    static void playStop(GAME_VOICE_HANDLE* voice);
    // 2.0.0's symbols name it (1.0.0's GfMenuObjMercenaryForm::update makes no such call). What it does: forwards its
    // one argument to SCOM_FIELD_VOICE::playStop (gf_req_scom), which searches GfReqSmallCom's list for the entry
    // holding that handle. Callers: GfMenuObjMercenaryForm::update and seqLeaveBlade (a long kept as -1 for none),
    // GfMenuObjMercenaryReport::update, GfMenuObjBlKizunaRing::finalize and its RingListener.
    static void playStop(GF_SCOM_HANDLE* voice);
    // waitForOthers: the voice waits while an object of type 3 or 4 has a voice playing (3.0.1 added the
    // parameter: 1.0.0's playVoice has three)
    static GAME_VOICE_HANDLE* playVoice(const ParamObj& obj, const char* name, CV_PRIO prio, bool waitForOthers);
    static GAME_VOICE_HANDLE* playVoice(GF_OBJ_HANDLE* handle, const char* name, CV_PRIO prio);
    static GAME_VOICE_HANDLE* playVoice(unsigned int type, unsigned int id, const char* name, CV_PRIO prio);
    // 2.0.0's symbols name it. What it does: plays a voice for the object of a kind and an ID (ParamObj(type, id)) that
    // waits while another object's voice plays (playVoice's waitForOthers true); its one caller is createDriverForIra.
    static GAME_VOICE_HANDLE* playVoiceParty(unsigned int type, unsigned int id, const char* name, CV_PRIO prio);
    // 2.0.0's symbols name it. What it does: plays a voice for an object (playVoice(ParamObj(handle), name, prio,
    // false)), then sets waitForOthers on the slot that plays it; its one caller is createInPartyForIra.
    static GAME_VOICE_HANDLE* playVoiceParty(GF_OBJ_HANDLE* handle, const char* name, CV_PRIO prio);
    // plays the named voice ("702870101"), handing back its handle for getResult
    static GAME_VOICE_HANDLE* playVoice(const char* name);
    static CV_RESULT getResult(GAME_VOICE_HANDLE* voice);
    static CV_RESULT getResult(GF_OBJ_HANDLE* handle);  // the voice of an object (GfGameUtil::isPlayVoice: 2 playing)
    // the slot playing obj's voice (1.0.0's gf::GfGameVoice::getPlayInfo(ParamObj const&), 0x71003590C0; 3.0.1
    // inlines it)
    static VoiceInfo* getPlayInfo(const ParamObj& obj) {
        GfGameVoice* self = sys();
        mm::mtl::FixedList<VoiceInfo*, 6>::iterator it = self->m_playList.begin();
        for (; it != self->m_playList.end(); ++it) {
            if ((*it)->m_obj == obj) {
                break;
            }
        }
        return it != self->m_playList.end() ? *it : nullptr;
    }
    bool isPlayEnemyVoice() const;
    static void gevMapjump(gf::GEV gev, const gf::MapjumpCallbackInfo& info);
    bool isPlayVoice(gf::GF_OBJ_HANDLE* handle) const;

    // keeps how a voice ended, dropping the oldest when full (1.0.0's static gf::GfGameVoice::addResult, 0x710035A7AC;
    // 3.0.1 inlines it)
    static void addResult(const ParamObj& obj, GAME_VOICE_HANDLE* voice, CV_RESULT result) {
        GfGameVoice* self = sys();
        if (self->m_results.full()) {
            self->m_results.pop();
        }
        self->m_results.push_back(Result(obj, voice, result));
    }

    bool m_isInitialized;
    mm::mtl::FixedList<VoiceInfo*, 6> m_freeList;   // the slots no voice uses
    mm::mtl::FixedList<VoiceInfo*, 6> m_playList;   // the slots playing or queued
    unsigned long m_voiceCount;  // the last GAME_VOICE_HANDLE value playVoice handed out
    mm::mtl::FixedQueue<Result, 256> m_results;
};
}  // namespace gf

#endif
