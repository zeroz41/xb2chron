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

    SCOM_FIELD_VOICE()
        : SCOM(SCOM_TYPE(0x3f)), m_flagD0(false), m_flagD1(false), m_stopOnEvent(false),
          m_flagD3(false) {}
    // inline: the create functions queue their voices in place
    void add(const ParamObj& obj, CV_FIELD field, CV_PRIO prio, float wait = 0.0f) {
        m_voices.push_back(Voice(obj, field, prio, wait));
    }

    virtual bool exec(fw::UpdateInfo const&);  // slot 2
    // plays at once (no request) for the object the player controls
    static GAME_VOICE_HANDLE* create(CV_FIELD field, CV_PRIO prio);
    // the bad weather voice and a time range's voice (GfGameScene::gevChangeWeather and gevChangeTimeRange call them
    // and ignore what they return, so the return type is not established)
    static void createBadWeather();
    static void createTime(CV_FIELD field);
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
    static unsigned long createMercenariesStart(unsigned int id);
    static unsigned long createMercenariesEnd(unsigned int id);
    static unsigned long createMercenariesResult(unsigned int id);
    static unsigned long createLandmark();

    // Placeholder name: nothing names it (1.0.0 has it unnamed too, at 0x71005CFB94, called from the same three
    // create functions). A member because only SCOM_FIELD_VOICE's createMercenariesStart/End/Result call it, in this
    // file. What it does: asks GfDataBlade's fn_7100238EC8(i, 0) for i = 0, 1, 2, keeps the non-zero answers
    // (16-bit blade IDs) in a 32-entry mm::mtl::FixedVector on its stack, and returns one picked by
    // ml::mtRand(count), or 0 when none; the callers queue a second voice for that blade (ParamObj(3, blade)).
    static unsigned int fn_7100567A44();

    // true while the voices are to be cut short: 1.0.0 has it out of line (m_stopOnEvent and
    // GfGameManager::isPlayEvent()); 3.0.1's exec inlines it and also tests m_flagD3
    bool isStopVoice() const;

    mm::mtl::FixedQueue<Voice, 4> m_voices;  // exec plays the first, then pops it
    bool m_flagD0;
    bool m_flagD1;
    bool m_stopOnEvent;  // 1.0.0's isStopVoice(): set and GfGameManager::isPlayEvent()
    bool m_flagD3;
};
}  // namespace gf

#endif
