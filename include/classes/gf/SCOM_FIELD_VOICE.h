#ifndef CLASSES_GF_SCOM_FIELD_VOICE_H
#define CLASSES_GF_SCOM_FIELD_VOICE_H

#include "classes/gf/SCOM.h"
#include "gf/ParamObj.h"
#include "mm/mtl/FixedQueue.h"

namespace fw { class UpdateInfo; }
namespace gf { enum CV_FIELD : int; enum CV_PRIO : int; }  // the field voice's kind and priority
namespace gf { enum FAVORITE : int; enum CV_RESULT : int; class GAME_VOICE_HANDLE; }

namespace gf {
// table 0x7100B6B690
class SCOM_FIELD_VOICE : public ::gf::SCOM {
public:
    // the voice names fn_7100568E1C and fn_7100569264 pick one of (ml::mtRand(m_count)); their callers fill it on the
    // stack. Up to five (m_count at 0x28); no destructor code follows the calls, so it is not mm::mtl::FixedVector
    // (that one clears its size on destruction). The name and the field names are not the original's.
    struct VoiceList {
        const char* m_names[5];
        unsigned long m_count;
    };
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because SCOM_FIELD_VOICE's
    // fn_71005691B0, fn_71005691EC, fn_7100568D34 and createFieldSkillMiss call it and it sits among its create
    // functions. What it does: when GfGameManager::fn_71002A9E68 holds, picks a party blade (fn_7100566B24,
    // ml::mtRand) of bdat id 0x11 and up and plays one of names (ml::mtRand(m_count)) for it, with the blade's name
    // from the table at 0x7100B6AB50; 0 when it plays nothing (not recovered).
    static GAME_VOICE_HANDLE* fn_7100568E1C(const VoiceList& names);
    // the names below are not the original's (what the create functions store and exec reads)
    // one voice to play: exec waits m_wait seconds, plays it (GfFieldVoice::playVoice(m_obj, m_field, m_prio)),
    // then waits for GfGameVoice::getResult(m_voice)
    struct Voice {
        Voice(const ParamObj& obj, CV_FIELD field, CV_PRIO prio, float wait)
            : m_obj(obj), m_wait(wait), m_field(field), m_state(CV_RESULT(0)), m_prio(prio), m_voice(0) {}

        ParamObj m_obj;
        float m_wait;
        CV_FIELD m_field;
        CV_RESULT m_state;  // 0 waiting, 2 playing (exec), then GfGameVoice::getResult's answer
        CV_PRIO m_prio;
        GAME_VOICE_HANDLE* m_voice;
    };

    // the party voices (createSkipTravel) pass true: they are cut short by an event
    SCOM_FIELD_VOICE(bool stopOnEvent = false)
        : SCOM(SCOM_TYPE(0x3f)), m_flagD0(false), m_flagD1(false), m_stopOnEvent(stopOnEvent),
          m_flagD3(false) {}
    // inline: the create functions queue their voices in place
    void add(const ParamObj& obj, CV_FIELD field, CV_PRIO prio, float wait = 0.0f) {
        m_voices.push_back(Voice(obj, field, prio, wait));
    }

    virtual bool exec(fw::UpdateInfo const&);  // slot 2
    // plays at once (no request) for the object the player controls
    static GAME_VOICE_HANDLE* create(CV_FIELD field, CV_PRIO prio);
    // the bad weather voice and a time range's voice (GfGameScene::gevChangeWeather and gevChangeTimeRange call them
    // and ignore what they return; createTime returns the request handle or -1, outside battle, for a party slot
    // fn_71005680B0 picks whose driver has HP and is valid: the driver's voice, then its partner's)
    static void createBadWeather();
    static unsigned long createTime(CV_FIELD field);
    // the voice for leaving an inn (GfMenuObjShop::seqStartSleepFade calls it and ignores what it returns): the
    // partner's voice, then the driver's (field 9), with m_flagD0 set; the request handle or -1
    static unsigned long createExitInn();
    // the restart voice (GfPlayComPlayerDead::update): like createTime (no battle test), each voice 0.5 s late
    static unsigned long createRestart(CV_FIELD field);
    // plays at once for obj, or for the object the player controls when obj names nothing (1.0.0 has it out of line;
    // 3.0.1 inlines every call)
    static GAME_VOICE_HANDLE* create(const ParamObj& obj, CV_FIELD field, CV_PRIO prio);
    static GAME_VOICE_HANDLE* createHighLanding(const ParamObj& obj);
    static GAME_VOICE_HANDLE* createJump(const ParamObj& obj);  // (by its symbol; the return type is not established)
    static GAME_VOICE_HANDLE* createFallDead(const ParamObj& obj);
    static GAME_VOICE_HANDLE* createMercenariesIn(unsigned int id);
    static GAME_VOICE_HANDLE* createMercenariesLeader(unsigned int id);
    static GAME_VOICE_HANDLE* createReleaseBlade(unsigned int id);
    static GAME_VOICE_HANDLE* createAchievement(unsigned int id, unsigned int);
    static GAME_VOICE_HANDLE* createEngage(unsigned int id);
    // the blade's voice (field 27) and, queued after it, its set driver's (or else its creator's) for the same field
    // (GfMenuObjBlKizunaRing::seqComplete); the request handle or -1
    static unsigned long createAchievementAll(unsigned int id);
    // the favourite voice of a driver or blade (GfMenuObjPouch2::procFavFlag returns what it returns)
    static GAME_VOICE_HANDLE* createFavorite(unsigned int id, FAVORITE favorite);
    static unsigned long createMercenariesStart(unsigned int id);
    // a driver's bond voice: one of three (ml::mtRand(3)) for driver id 1..6 (GfGameVoice::playVoice type 3);
    // nullptr for any other id
    static GAME_VOICE_HANDLE* createDriverKizuna(unsigned int id);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (1.0.0's createQuest(CV_FIELD) has the same
    // size but plays a voice through GfFieldVoice::playVoice; this takes no argument). A member because it sits among
    // this class's create functions in gf_req_scom (after createDriverKizuna). What it does: passes the voice pair
    // "670101"/"670102" (count 2) to fn_7100568E1C. Its one caller is GfMenuObjQuestLog::seqOrderWaitCtrl, after a
    // quest's order window when GfMenuObjUtil::fn_710048FD30(3) holds.
    static void fn_71005691B0();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member for the same reason (right after
    // fn_71005691B0). What it does: passes the voice pair "670103"/"670104" (count 2) to fn_7100568E1C. Its one
    // caller is GfMenuObjQuestLog::seqCompleteWait, after a quest's complete window when fn_710048FD30(3) holds.
    static void fn_71005691EC();
    // the voice when a field skill starts: GfDataBlade::getFieldSkillVoice(blade, skill) for the blade, at once
    // (0 when the blade has none). Caller: GfMenuObjFieldSkill::SkillInfoListener::reciveEvent.
    static GAME_VOICE_HANDLE* createFieldSkillStart(unsigned int blade, unsigned int skill);
    // Placeholder name (inferred: createFieldSkillSuccess): it sits between createFieldSkillStart and
    // createFieldSkillMiss and is their twin with QuestListAcc::getFLD_FieldSkillSettingSuccessVoiceCategory (voices
    // "750101"-"750103" first). Caller: GfMenuObjFieldSkill::ResultListener::reciveEvent on success.
    static GAME_VOICE_HANDLE* fn_7100568D34(unsigned int);
    // the voice when a field skill fails (QuestListAcc::getFLD_FieldSkillSettingMissVoiceCategory). Caller:
    // GfMenuObjFieldSkill::ResultListener::reciveEvent on failure.
    static GAME_VOICE_HANDLE* createFieldSkillMiss(unsigned int);
    static unsigned long createMercenariesEnd(unsigned int id);
    static unsigned long createMercenariesResult(unsigned int id);
    // the landmark (field 5) and unexplored-area (field 6) voices: outside battle, once GfGameScene::m_value634 is
    // 60 or more, for a party slot fn_71005680B0 picks whose driver has HP (createUnexplored: and is valid): the
    // driver (priority 1), then its partner (priority 3); the request handle or -1
    static unsigned long createLandmark();
    static unsigned long createUnexplored();

    // Placeholder name: nothing names it (1.0.0 has it unnamed too, at 0x71005CFB94, called from the same three
    // create functions). A member because only SCOM_FIELD_VOICE's createMercenariesStart/End/Result call it, in this
    // file. What it does: asks GfDataBlade's fn_7100238EC8(i, 0) for i = 0, 1, 2, keeps the non-zero answers
    // (16-bit blade IDs) in a 32-entry mm::mtl::FixedVector on its stack, and returns one picked by
    // ml::mtRand(count), or 0 when none; the callers queue a second voice for that blade (ParamObj(3, blade)).
    static unsigned int fn_7100567A44();
    // the skip-travel voice (field 19 when the argument holds, else 20) for the driver and its blade (Torna mode:
    // its second driver) of a party slot fn_71005680B0 picks; queued with m_stopOnEvent. Returns -1 whatever it
    // queues (GfReqCommand::execMapjump calls it).
    static unsigned long createSkipTravel(bool start);
    // Placeholder name: new in 3.0.1 (1.0.0 has no Torna-mode test in its place). A member because only
    // SCOM_FIELD_VOICE's create functions (createLandmark, createUnexplored, createExitInn, createSkipTravel,
    // createRestart, createBadWeather, createTime) call it. What it does: collects the party slots 0..2 whose
    // driver and blade are valid game objects (GfGameObj::isValidGameObj(handle, true, null); when
    // GfGameManager::fn_71002A9E68 holds, whose two GfGameParty::getDriverBdatId(slot, 0/1) are non-zero) in a
    // 32-entry mm::mtl::FixedVector<unsigned short> and returns one picked by ml::mtRand(count), or -1 when none.
    static int fn_71005680B0();

    // true while the voices are to be cut short: 1.0.0 has it out of line (m_stopOnEvent and
    // GfGameManager::isPlayEvent()); 3.0.1's exec inlines it and also tests m_flagD3
    bool isStopVoice() const;

    mm::mtl::FixedQueue<Voice, 4> m_voices;  // exec plays the first, then pops it
    bool m_flagD0;
    bool m_flagD1;
    bool m_stopOnEvent;  // 1.0.0's isStopVoice(): set and GfGameManager::isPlayEvent()
    bool m_flagD3;
};

// Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them. Free functions: they take no this, and their
// callers are menu code outside any SCOM class. What fn_7100569264 does: when GfGameManager::fn_71002A9E68 holds and
// blade is a bdat id 0x11..0x19, plays one of names (ml::mtRand(m_count)) appended to the blade's name (table
// 0x7100B6AB50) for the blade (GfGameVoice::fn_71002F1D20(3, blade, ...)); 0 otherwise (not recovered). The others
// pass it fixed lists: fn_71005693C0 "680101"/"680102" (caller fn_71003BD208), fn_71005695D0 "700101".."700103"
// (caller GfMenuObjDrArtsSet2::ArtsListListener::reciveEvent), fn_7100569618 "710101".."710103" (caller
// GfMenuObjDrKizunaRing::seqSkillAnime).
GAME_VOICE_HANDLE* fn_7100569264(unsigned int blade, const SCOM_FIELD_VOICE::VoiceList& names);
GAME_VOICE_HANDLE* fn_71005693C0(unsigned int blade);  // fn_7100569264's voice (fn_71003BD208 keeps it)
void fn_71005695D0(unsigned int blade);
void fn_7100569618(unsigned int blade);
}  // namespace gf

#endif
