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

bool TalkManager::fn_71000AA39C() const {
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

bool TalkManager::fn_71000AEAB4(gf::GF_OBJ_HANDLE* handle, unsigned int id, bool noObject) {
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
    if (character->fn_7100028D0C(true)) {
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

void TalkManager::fn_71000AF7FC(unsigned int index, float time) {
    if (m_timeA[index] > time) {
        time = m_timeA[index];
    }
    m_timeA[index] = time;
}

}  // namespace btl
