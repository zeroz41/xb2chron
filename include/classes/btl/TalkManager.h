#ifndef CLASSES_BTL_TALKMANAGER_H
#define CLASSES_BTL_TALKMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/FixedList.h"
#include "mm/mtl/FixedVector.h"
#include <string.h>

namespace btl { class TalkManager; class BattleCharacter; }
namespace fw { class UpdateInfo; }
namespace gf { class GAME_VOICE_HANDLE; class GF_OBJ_HANDLE; }
class CBdatWrapper;

namespace btl {
// table 0x7100B3BDE8; the battle's voice lines (1.0.0's TalkManager symbols name the members and types)
class TalkManager : public ::mm::mtl::PtrSingleton< ::btl::TalkManager> {
public:
    enum NARRATION_TYPE : int;
    // unsigned: SetTriggerInterval indexes m_timeA with it zero-extended (uxtw)
    enum TRIGGER : unsigned int;
    // the column GetBdatData reads, by the column's name in tables 0x55-0x58 (the enumerator names are not the
    // original's)
    enum BDAT_DATA_TYPE : int {
        BDAT_PRIORITY,
        BDAT_GROUP,
        BDAT_CT_DRIVER,
        BDAT_ENEMY_VC,
        BDAT_COND_0,
        BDAT_COND_1,
        BDAT_LOT_RATE,
        BDAT_REPLY,
        BDAT_REPLY_GROUP,
        BDAT_VOICE_0,
        BDAT_VOICE_1,
        BDAT_VOICE_2,
        BDAT_VOICE_3,
        BDAT_REP_BUDDY,
        BDAT_LOT_NUM,
        BDAT_NO_OVERWRITE,
        BDAT_DEAD,
        BDAT_NO_DIR,
        BDAT_NO_CHAIN,
        BDAT_NO_REPLY_OK,
        BDAT_SERIOUS_OFF,
        BDAT_INTERVAL,
        BDAT_SOLO_MODE,
        BDAT_COND_EX,
    };

    // a registered voice line, 0x20 bytes (the field names are not the original's)
    struct CHR_VOICE_DATA {
        gf::GF_OBJ_HANDLE* m_handle;     // the speaker's object (PlaySpWin replaces its entry); -1 when UpdateProc
                                         // drops the entry
        gf::GAME_VOICE_HANDLE* m_voice;  // the playing voice (UpdateProc asks GfGameVoice::getResult)
        // the BDAT table the line comes from: 1-3 tables 0x55-0x57 (3: an enemy's), 4 table 0x58 or 0x59
        unsigned int m_type : 3;
        unsigned int m_voiceId : 10;   // the row of that table
        unsigned int m_chrIndex : 7;   // the speaker (IsTalk, GetPlayVoiceID compare it)
        unsigned int pad_bits20 : 4;   // PlaySpWin sets 15 (meaning unknown)
        unsigned int pad_bits24 : 8;   // UpdateProc clears the whole word with the entry (meaning unknown)
        unsigned int : 0;
        bool pad_bit0 : 1;
        bool pad_bit1 : 1;
        bool m_nextRegistered : 1;  // set before UpdateProc registers the next voice
        bool pad_bit3 : 1;  // PlaySpWin: the row's "Timer" is not 0
        bool pad_bit4 : 1;  // PlaySpWin: played without an object
        bool pad_bit5 : 1;  // IsTalkSirenSp tests it
        bool pad_bit6 : 1;
        bool pad_bit7 : 1;
        unsigned char pad_15[4];  // 0x5A each when UpdateProc drops the entry
        unsigned char pad_19[7];
    };
    // GetBdatData's result, returned in x0/x1: the column's value (zero-extended from its width) and whether the
    // type was unknown (the names are not the original's)
    struct BDAT_VALUE {
        union {
            bool m_flag;
            unsigned char m_u8;
            unsigned short m_u16;
            float m_float;
            unsigned long m_u64;
        };
        bool m_isNone;
    };
    // a speaker's pause between lines, kept in m_intervals (the field names are not the original's)
    struct CHR_INTERVAL_DATA {
        float m_time;  // counted down by UpdateProc; the entry goes at 0
        int pad_4;
    };
    // StartBattleCallback counts m_count down and drops the entry at 0 (the names are not the original's)
    struct COUNT_DATA {
        unsigned short m_voiceRow;  // the row PlaySpWin played (the name is not the original's)
        unsigned char m_count;
        unsigned char pad_3;
    };
    // the first rows of a voice group in tables 0x55-0x57, by group (the names are not the original's)
    struct GROUP_TOP {
        unsigned short m_top;
        unsigned short m_second;
    };

    TalkManager() : m_narrationVoice(nullptr), m_narrationState(0), m_narrationType(5) {
        memset(m_timeA, 0, sizeof(m_timeA));
        memset(m_timeB, 0, sizeof(m_timeB));
        ResetVoiceGroupID();
        pad_1a2e = 0;
        pad_1a2f = 0;
        m_isTimeA = false;
        m_isTimeB = false;
    }
    virtual ~TalkManager();  // slot 0
    void ResetVoiceGroupID() { memset(m_groupTop, 0, sizeof(m_groupTop)); }
    static void Create();
    void Initialize();
    static void Destroy();
    void Finalize();
    void InitializeGroupTopData();
    void NotifyMapChange();
    bool IsTalk(int chr) const;
    // 2.0.0's symbols name it. What it does: true when one of the entries (count at +0xB50, 0x20 bytes apart from
    // +0x24) has bit 5 of its first byte set.
    bool IsTalkSirenSp() const;
    bool IsEnableFieldBladeChange() const;
    bool IsPlayingEnemyVoice() const;
    bool IsPlayingEnemyWinVoice() const;
    static void PreUpdate(const fw::UpdateInfo& info);
    void PreUpdateProc(const fw::UpdateInfo& info);
    static void Update(const fw::UpdateInfo& info);
    void UpdateProc(const fw::UpdateInfo& info);
    void RegisterNextVoice(const CHR_VOICE_DATA& data);
    // false when the line is not registered (PlayVoice(int, int) returns 0 then)
    bool RegisterTalk(int, int, int, int, int, int, bool);
    void StartBattleCallback();
    BDAT_VALUE GetBdatData(CBdatWrapper& bdat, unsigned int id, BDAT_DATA_TYPE type) const;
    int DecideVoiceBdatID(int, int, int, int, int);
    void RegisterSpecialWin();
    bool IsBladeChangeCondition(int, int, BattleCharacter* chr) const;
    // 2.0.0's symbols name it. A member because RegisterSpecialWin calls it
    // on this. What it does: plays row id's "Voice" of BDAT table 0x58 (0x59 while BattleGlobal's
    // m_challengeAnySuccess) for handle (or, when the flag is set, without an object), puts it in m_voices in place
    // of handle's entry, and records id in m_counts (dropping the oldest when full). False when nothing plays.
    bool PlaySpWin(gf::GF_OBJ_HANDLE* handle, int id, bool);
    const CHR_VOICE_DATA* GetRegisterDataConst(int chr) const {
        for (const CHR_VOICE_DATA* it = m_voices.begin(); it != m_voices.end(); ++it) {
            if (it->m_chrIndex == chr) {
                return it;
            }
        }
        return nullptr;
    }
    // 1.0.0 has this overload out of line (0x710008D260); 3.0.1 inlines it
    const CHR_VOICE_DATA* GetRegisterDataConst(gf::GF_OBJ_HANDLE* handle) const {
        for (const CHR_VOICE_DATA& data : m_voices) {
            if (data.m_handle == handle) {
                return &data;
            }
        }
        return nullptr;
    }
    int GetPlayVoiceID(int chr) const;
    // whether a voice was triggered (CharacterManager::PlayEnemyWinVoice stops at the first true)
    bool NotifyTrigger(int, TRIGGER, int, int);
    // the entry's 64-bit value, 0 when none plays (Utility::AI_PlayVoice returns it)
    unsigned long PlayVoice(int, int);
    unsigned long PlayVoice(int, const char*);
    void PlayNarrationVoice(NARRATION_TYPE type, int, int);
    // 2.0.0's symbols name it. A member because SirenBattleManager's update
    // passes the TalkManager singleton and it sits in talk_manager_battle's range. What it does: raises
    // m_timeA[index] to time when it is below.
    void SetTriggerInterval(TRIGGER index, float time);

    gf::GAME_VOICE_HANDLE* m_narrationVoice;  // NotifyMapChange stops it (the name is not the original's)
    ::mm::mtl::FixedVector<CHR_VOICE_DATA, 90> m_voices;
    ::mm::mtl::FixedVector<COUNT_DATA, 4> m_counts;
    ::mm::mtl::FixedList<CHR_INTERVAL_DATA, 200> m_intervals;
    // timers by 1-based id, counted down to 0 by UpdateProc while m_isTimeA / m_isTimeB (the names are not the
    // original's)
    float m_timeA[63];
    float m_timeB[112];
    GROUP_TOP m_groupTop[112];  // by the "Group" column's value
    unsigned char m_narrationState;  // NotifyMapChange and UpdateProc set it to 0 (the name is not the original's)
    unsigned char m_narrationType;   // NotifyMapChange and UpdateProc set it to 5 (the name is not the original's)
    unsigned char pad_1a2e;
    unsigned char pad_1a2f;
    bool m_isTimeA;
    bool m_isTimeB;
    unsigned char pad_1a32[6];
};
}  // namespace btl

#endif
