#include "btl/challenge_battle_manager.h"
#include "classes/btl/BattleGlobal.h"
#include "classes/btl/BtlSystemBalanceAccess.h"
#include "classes/btl/CharacterManager.h"
#include "classes/gf/GfReqSmallCom.h"
#include "btl/challenge_battle_manager.h"
#include "classes/btl/BattleCharacter.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfReqSmallCom.h"
#include "classes/gf/SCOM_ADD_ECUBE.h"
#include "plugin/Bdat.h"
#include "classes/btl/BattleGlobal.h"
#include "classes/btl/BtlSystemBalanceAccess.h"
#include "classes/btl/CharacterManager.h"
#include "classes/btl/TalkManager.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfGameManager.h"

namespace btl {

void ChallengeBattleManager::Create() {
#line 98
    new (gf::getAllocator(gf::ALLOCATOR(0)), __FILE__, __LINE__, 8) ChallengeBattleManager;
}

void ChallengeBattleManager::Destroy() {
    delete ChallengeBattleManager::get();
}

bool ChallengeBattleManager::IsProc() const {
    return pad_26 != 0;
}

void ChallengeBattleManager::NotifyStartTelop() {
    TalkManager::get()->PlayNarrationVoice(TalkManager::NARRATION_TYPE(0x30), 0, 0);
    pad_1c = 2.75f;
}

void ChallengeBattleManager::Update(const fw::UpdateInfo& info) {
    ChallengeBattleManager::get()->UpdateProc(info);
}

bool ChallengeBattleManager::IsResult() const {
    return pad_26 > 149;
}

bool ChallengeBattleManager::IsExit() const {
    return pad_26 > 199;
}

void ChallengeBattleManager::SetBGMID(unsigned int value) {
    if (pad_26 != 0) {
        pad_24 = value;
    }
}

void ChallengeBattleManager::AddEtherCube(int value) {
    if (value != 0 && pad_26 != 0) {
        gf::SCOM_ADD_ECUBE::create(value);
    }
}

float ChallengeBattleManager::GetDropEtherCubeRate() const {
    return BattleGlobal::get()->pad_5c50;
}

float ChallengeBattleManager::GetWinWalkRestTime(bool& flag) const {
    if (pad_26 != 160) {
        flag = false;
        return -1.0f;
    }
    float limit = BtlSystemBalanceAccess::get()->pad_120;
    float rest = limit - pad_18;
    bool low;
    if (rest <= 0.0f) {
        rest = 0.0f;
        low = true;
    } else if (rest >= limit) {
        rest = limit;
        low = false;
    } else {
        low = rest / limit < 0.3f;
    }
    flag = rest <= 5.0f || low;
    return rest;
}

bool ChallengeBattleManager::IsRetryProc() const {
    if (pad_26 == 201 && gf::GfGameManager::isFadeout()) {
        return true;
    }
    return false;
}

bool ChallengeBattleManager::IsWaveInterval() const {
    return pad_26 >= 100 && pad_26 < 150;
}

bool ChallengeBattleManager::IsEnableAutoHeal() const {
    if (pad_26 == 0) {
        return false;
    }
    if (pad_29 == 3) {
        return !CharacterManager::get()->IsExistBattleEnemy(nullptr, reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1), false);
    }
    return IsWaveInterval();
}

bool ChallengeBattleManager::IsWin() const {
    return pad_26 >= 157 && pad_26 < 162;
}

bool ChallengeBattleManager::IsEnableOperate() const {
    if (pad_26 == 0) {
        return true;
    }
    return pad_2b != 0;
}

bool ChallengeBattleManager::IsEnableReturnHome() const {
    if (pad_26 == 0) {
        return true;
    }
    return pad_29 == 3;
}

bool ChallengeBattleManager::IsChallengeTimeWarning() const {
    return gf::GfGameManager::getBattleArenaMenuInfo()->m_value4 - pad_10 <= 300.0f;
}

}  // namespace btl
