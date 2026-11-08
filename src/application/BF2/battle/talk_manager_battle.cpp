#include "classes/btl/TalkManager.h"
#include "classes/btl/BattleCharacter.h"
#include "classes/btl/BattleGlobal.h"
#include "classes/btl/CharacterManager.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfGameVoice.h"
#include "fw/UpdateInfo.h"
#include "plugin/Bdat.h"
#include "mm/mtl/FixStr.h"
#include <algorithm>

namespace btl {

TalkManager::~TalkManager() {}

void TalkManager::Create() {
#line 96
    TalkManager* manager = new (gf::getAllocator(gf::ALLOCATOR(0)), __FILE__, __LINE__, 8) TalkManager;
    manager->Initialize();
}

void TalkManager::Initialize() {
    InitializeGroupTopData();
}

void TalkManager::Destroy() {
    delete get();
}

void TalkManager::Finalize() {}

void TalkManager::NotifyMapChange() {
    m_intervals.clear();
    if (m_narrationVoice != nullptr) {
        gf::GfGameVoice::playStop(m_narrationVoice);
        m_narrationVoice = nullptr;
    }
    m_narrationState = 0;
    m_narrationType = 5;
}

bool TalkManager::IsTalk(int chr) const {
    if (chr < 0) {
        return !m_voices.empty();
    }
    return std::any_of(m_voices.begin(), m_voices.end(),
                       [chr](const CHR_VOICE_DATA& data) { return data.m_chrIndex == chr; });
}

bool TalkManager::IsTalkSirenSp() const {
    return std::any_of(m_voices.begin(), m_voices.end(), [](const CHR_VOICE_DATA& data) { return data.pad_bit5; });
}

bool TalkManager::IsEnableFieldBladeChange() const {
    return true;
}

bool TalkManager::IsPlayingEnemyVoice() const {
    return std::any_of(m_voices.begin(), m_voices.end(), [](const CHR_VOICE_DATA& data) { return data.m_type == 3; });
}

void TalkManager::PreUpdate(const fw::UpdateInfo& info) {
    get()->PreUpdateProc(info);
}

void TalkManager::PreUpdateProc(const fw::UpdateInfo& info) {}

void TalkManager::Update(const fw::UpdateInfo& info) {
    get()->UpdateProc(info);
}

void TalkManager::UpdateProc(const fw::UpdateInfo& info) {
    float dt = info.m_deltaTime;
    if (m_isTimeA) {
        bool counting = false;
        for (int i = 1; i < 63; i++) {
            float time = m_timeA[i] - dt;
            m_timeA[i] = time > 0.0f ? time : 0.0f;
            counting |= time > 0.0f;
        }
        m_isTimeA = counting;
    }
    if (m_isTimeB) {
        bool counting = false;
        for (int i = 1; i < 112; i++) {
            float time = m_timeB[i] - dt;
            m_timeB[i] = time > 0.0f ? time : 0.0f;
            counting |= time > 0.0f;
        }
        m_isTimeB = counting;
    }
    for (::mm::mtl::FixedList<CHR_INTERVAL_DATA, 200>::iterator it = m_intervals.begin(); it != m_intervals.end();) {
        float time = (*it).m_time - dt;
        if (time <= 0.0f) {
            it = m_intervals.erase(it);
        } else {
            it->m_time = time;
            ++it;
        }
    }
    for (CHR_VOICE_DATA* it = m_voices.begin(); it != m_voices.end();) {
        gf::GAME_VOICE_HANDLE* voice = it->m_voice;
        int result = gf::GfGameVoice::getResult(voice);
        if (it->pad_bit3 || it->m_nextRegistered || result != 2) {
            if (BattleGlobal::sys()->IsEnableBattle() && result != 4 && !it->m_nextRegistered &&
                (it->pad_bit3 || result == 6 || result == 3)) {
                it->m_nextRegistered = true;
                RegisterNextVoice(*it);
            }
            if (it->m_voice == voice) {
                CHR_VOICE_DATA empty;
                empty.m_handle = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
                empty.m_voice = nullptr;
                empty.m_type = 0;
                empty.m_voiceId = 0;
                empty.m_chrIndex = 0;
                empty.pad_bits20 = 0;
                empty.pad_bits24 = 0;
                empty.pad_bit0 = false;
                empty.pad_bit1 = false;
                empty.m_nextRegistered = false;
                empty.pad_bit3 = false;
                empty.pad_bit4 = false;
                empty.pad_bit5 = false;
                empty.pad_bit6 = false;
                empty.pad_bit7 = false;
                memset(empty.pad_15, 0x5A, sizeof(empty.pad_15));
                *it = empty;
                it = m_voices.erase(it);
                continue;
            }
        }
        ++it;
    }
    if (m_narrationVoice != nullptr && gf::GfGameVoice::getResult(m_narrationVoice) != 2) {
        m_narrationVoice = nullptr;
        m_narrationState = 0;
        m_narrationType = 5;
    }
}

void TalkManager::StartBattleCallback() {
    for (COUNT_DATA* it = m_counts.begin(); it != m_counts.end();) {
        if (it->m_count == 0) {
            it = m_counts.erase(it);
        } else {
            it->m_count--;
            ++it;
        }
    }
}

TalkManager::BDAT_VALUE TalkManager::GetBdatData(CBdatWrapper& bdat, unsigned int id, BDAT_DATA_TYPE type) const {
    BDAT_VALUE value;
    switch (type) {
    case BDAT_PRIORITY:
        value.m_u32 = Bdat::getValCheckU8(bdat.m_fp, "Priority", id);
        value.m_isNone = false;
        break;
    case BDAT_GROUP:
        value.m_u32 = Bdat::getValCheckU8(bdat.m_fp, "Group", id);
        value.m_isNone = false;
        break;
    case BDAT_CT_DRIVER:
        value.m_u32 = Bdat::getValCheckU16(bdat.m_fp, "CTDriver", id);
        value.m_isNone = false;
        break;
    case BDAT_ENEMY_VC:
        value.m_u32 = Bdat::getValCheckU16(bdat.m_fp, "EnemyVC", id);
        value.m_isNone = false;
        break;
    case BDAT_COND_0:
        value.m_u32 = static_cast<unsigned char>(Bdat::getArrayValCheck(bdat.m_fp, "Cond", id, 0, 1));
        value.m_isNone = false;
        break;
    case BDAT_LOT_RATE: {
        float rate = Bdat::getValCheckU8(bdat.m_fp, "LotRate", id) * 0.01f;
        memcpy(&value.m_float, &rate, sizeof(rate));
        value.m_isNone = false;
        break;
    }
    case BDAT_REPLY:
        value.m_u32 = Bdat::getValCheckU16(bdat.m_fp, "Reply", id);
        value.m_isNone = false;
        break;
    case BDAT_REPLY_GROUP:
        value.m_u32 = Bdat::getValCheckU8(bdat.m_fp, "ReplyGroup", id);
        value.m_isNone = false;
        break;
    case BDAT_VOICE_0:
        value.m_u64 = Bdat::getArrayValCheck(bdat.m_fp, "Voice", id, 0, 7);
        value.m_isNone = false;
        break;
    case BDAT_VOICE_1:
        value.m_u64 = Bdat::getArrayValCheck(bdat.m_fp, "Voice", id, 1, 7);
        value.m_isNone = false;
        break;
    case BDAT_VOICE_2:
        value.m_u64 = Bdat::getArrayValCheck(bdat.m_fp, "Voice", id, 2, 7);
        value.m_isNone = false;
        break;
    case BDAT_VOICE_3:
        value.m_u64 = Bdat::getArrayValCheck(bdat.m_fp, "Voice", id, 3, 7);
        value.m_isNone = false;
        break;
    case BDAT_REP_BUDDY:
        value.m_flag = Bdat::getFlagVal(bdat.m_fp, "Flag", id, "RepBuddy") != 0;
        value.m_isNone = false;
        break;
    case BDAT_LOT_NUM:
        value.m_flag = Bdat::getFlagVal(bdat.m_fp, "Flag", id, "LotNum") != 0;
        value.m_isNone = false;
        break;
    case BDAT_NO_OVERWRITE:
        value.m_flag = Bdat::getFlagVal(bdat.m_fp, "Flag", id, "NoOverwrite") != 0;
        value.m_isNone = false;
        break;
    case BDAT_DEAD:
        value.m_flag = Bdat::getFlagVal(bdat.m_fp, "Flag", id, "Dead") != 0;
        value.m_isNone = false;
        break;
    case BDAT_NO_DIR:
        value.m_flag = Bdat::getFlagVal(bdat.m_fp, "Flag", id, "NoDir") != 0;
        value.m_isNone = false;
        break;
    case BDAT_NO_CHAIN:
        value.m_flag = Bdat::getFlagVal(bdat.m_fp, "Flag", id, "NoChain") != 0;
        value.m_isNone = false;
        break;
    case BDAT_NO_REPLY_OK:
        value.m_flag = Bdat::getFlagVal(bdat.m_fp, "Flag", id, "NoReplyOK") != 0;
        value.m_isNone = false;
        break;
    case BDAT_SERIOUS_OFF:
        value.m_flag = Bdat::getFlagVal(bdat.m_fp, "Flag", id, "SeriousOff") != 0;
        value.m_isNone = false;
        break;
    case BDAT_INTERVAL:
        value.m_u32 = Bdat::getValCheckU8(bdat.m_fp, "Interval", id);
        value.m_isNone = false;
        break;
    case BDAT_SOLO_MODE:
        value.m_u32 = Bdat::getValCheckU8(bdat.m_fp, "SoloMode", id);
        value.m_isNone = false;
        break;
    case BDAT_COND_EX:
        value.m_u32 = Bdat::getValCheckU16(bdat.m_fp, "CondEx", id);
        value.m_isNone = false;
        break;
    // last in the source: the original gives this case its own tail block (the last case of a switch gets one)
    case BDAT_COND_1:
        value.m_u32 = static_cast<unsigned char>(Bdat::getArrayValCheck(bdat.m_fp, "Cond", id, 1, 1));
        value.m_isNone = false;
        break;
    }
    return value;
}

bool TalkManager::PlaySpWin(gf::GF_OBJ_HANDLE* handle, int id, bool noObject) {
    unsigned char* fp = gf::GfDataBdat::getFP(0x58 | BattleGlobal::sys()->m_challengeAnySuccess);
    unsigned int voiceId = Bdat::getArrayValCheck(fp, "Voice", id, 0, 3);
    gf::GAME_VOICE_HANDLE* voice;
    {
        mm::mtl::FixStr<16> name;
        if (voiceId < 10000000) {
            name.format("%08u", voiceId);
        } else {
            name.format("%u", voiceId);
        }
        if (noObject) {
            voice = gf::GfGameVoice::playVoice(name.m_str);
        } else {
            voice = gf::GfGameVoice::playVoice(handle, name.m_str, static_cast<gf::CV_PRIO>(2));
        }
    }
    if (voice == nullptr) {
        return false;
    }
    CHR_VOICE_DATA data;
    data.m_handle = handle;
    data.m_voice = voice;
    data.m_type = 4;
    data.m_voiceId = id;
    data.m_chrIndex = 0;
    data.pad_bits20 = 15;
    data.pad_bit0 = false;
    data.pad_bit1 = false;
    data.m_nextRegistered = false;
    unsigned short timer = Bdat::getArrayValCheckU16(fp, "Timer", id, 0);
    data.pad_bit3 = timer != 0;
    data.pad_bit4 = noObject;
    data.pad_bit5 = false;
    data.pad_bit6 = false;
    data.pad_bit7 = false;
    memset(data.pad_15, 0x5A, sizeof(data.pad_15));
    CHR_VOICE_DATA* entry = const_cast<CHR_VOICE_DATA*>(GetRegisterDataConst(handle));
    if (entry != nullptr) {
        *entry = data;
    } else {
        m_voices.push_back(data);
    }
    if (m_counts.size() >= 4) {
        m_counts.erase(m_counts.begin());
    }
    COUNT_DATA count = {static_cast<unsigned short>(id), 3, 0};
    m_counts.push_back(count);
    return true;
}

int TalkManager::GetPlayVoiceID(int chr) const {
    const CHR_VOICE_DATA* data = GetRegisterDataConst(chr);
    return data != nullptr ? data->m_voiceId : 0;
}

unsigned long TalkManager::PlayVoice(int chr, int voice) {
    BattleCharacter* character = CharacterManager::sys()->GetCharacterConst(chr);
    if (character == nullptr) {
        return 0;
    }
    int kind;
    if (character->IsBlade(true)) {
        kind = 2;
    } else {
        kind = character->IsPlayer() ? 1 : 3;
    }
    if (!RegisterTalk(chr, voice, kind, -1, 0, 0, false)) {
        return 0;
    }
    const CHR_VOICE_DATA* data = GetRegisterDataConst(chr);
    if (data == nullptr) {
        return 0;
    }
    return reinterpret_cast<unsigned long>(data->m_voice);
}

unsigned long TalkManager::PlayVoice(int chr, const char* name) {
    BattleCharacter* character = CharacterManager::sys()->GetCharacterConst(chr);
    if (character == nullptr || character->m_handle == reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        return 0;
    }
    gf::GAME_VOICE_HANDLE* voice = gf::GfGameVoice::playVoice(character->m_handle, name, static_cast<gf::CV_PRIO>(2));
    if (voice != nullptr) {
        CHR_VOICE_DATA data;
        data.m_handle = character->m_handle;
        data.m_voice = voice;
        data.m_type = 0;
        data.m_voiceId = 0;
        data.m_chrIndex = chr;
        data.pad_bits20 = 0;
        data.pad_bit0 = false;
        data.pad_bit1 = false;
        data.m_nextRegistered = false;
        data.pad_bit3 = false;
        data.pad_bit4 = false;
        data.pad_bit5 = false;
        data.pad_bit6 = false;
        data.pad_bit7 = false;
        memset(data.pad_15, 0x5A, sizeof(data.pad_15));
        CHR_VOICE_DATA* entry = const_cast<CHR_VOICE_DATA*>(GetRegisterDataConst(chr));
        if (entry != nullptr) {
            *entry = data;
        } else {
            m_voices.push_back(data);
        }
    }
    return reinterpret_cast<unsigned long>(voice);
}

void TalkManager::SetTriggerInterval(TRIGGER index, float time) {
    if (m_timeA[index] > time) {
        time = m_timeA[index];
    }
    m_timeA[index] = time;
}

}  // namespace btl
