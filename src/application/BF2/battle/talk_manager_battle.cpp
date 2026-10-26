#include "classes/btl/TalkManager.h"
#include "classes/btl/BattleGlobal.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfGameVoice.h"
#include "fw/UpdateInfo.h"
#include "plugin/Bdat.h"

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

bool TalkManager::IsEnableFieldBladeChange() const {
    return true;
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

int TalkManager::GetPlayVoiceID(int chr) const {
    const CHR_VOICE_DATA* data = GetRegisterDataConst(chr);
    return data != nullptr ? data->m_voiceId : 0;
}

void TalkManager::fn_71000AF7FC(unsigned int index, float time) {
    if (m_timeA[index] > time) {
        time = m_timeA[index];
    }
    m_timeA[index] = time;
}

}  // namespace btl
