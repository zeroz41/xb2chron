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
#include "classes/btl/DataManager.h"
#include "classes/btl/SpAttackManager.h"
#include "classes/btl/ChainAttackManager.h"
#include "classes/gf/GfMenuReference.h"
#include "classes/gf/GfMenuObjBtlTime.h"
#include "classes/gf/SCOM_ADD_SCORE.h"
#include "classes/gmk/GmkBattleChallenge.h"
#include "classes/btl/BladeChangeManager.h"
#include "classes/fw/PadManager.h"
#include "classes/gf/GfMenuManager.h"
#include "fw/PadData.h"
#include "classes/btl/CharacterParameter.h"
#include "classes/fw/FrameworkMemory.h"
#include "classes/gf/GfFobjDropitem.h"
#include "ml/MTRand.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuObjBtlchTelop.h"
#include "classes/gf/GfGameArena.h"
#include "classes/gf/GfArenaBattle.h"
#include "classes/btl/UIManager.h"
#include "btl/Utility.h"
#include "classes/gf/SCOM_BATTLE_ARENA.h"
#include "classes/gf/SCOM_CLEAR_TIME.h"
#include "classes/gf/GfMenuObjSalvage.h"
#include <math.h>

namespace btl {

void ChallengeBattleManager::Create() {
#line 98
    new (gf::getAllocator(gf::ALLOCATOR(0)), __FILE__, __LINE__, 8) ChallengeBattleManager;
}

void ChallengeBattleManager::Destroy() {
    delete ChallengeBattleManager::get();
}

void ChallengeBattleManager::Start() {
    if (pad_26 != 0) {
        return;
    }
    if (pad_8 != nullptr) {
        pad_8->release();
        pad_8 = nullptr;
    }
    pad_10 = 0.0f;
    pad_14 = 0.0f;
    pad_18 = 0.0f;
    pad_1c = 0.0f;
    gf::GfMenuReference::setBattleTime(0.0f);
    pad_20 = 0;
    pad_22 = 0;
    DataManager::get()->SetPartyGauge(0, false);
    gf::GfMenuObjBtlTime::reset();
    pad_24 = 0;
    pad_28 = 0;
    pad_29 = 4;
    pad_2a = 0;
    pad_2b = 0;
    pad_2c = 0;
    pad_2d = 0;
    pad_20 = gmk::GmkBattleChallenge::sm_battleStatus.m_waveNum;
    pad_22 = gmk::GmkBattleChallenge::sm_battleStatus.m_waveIndex;
    pad_26 = 1;
}

bool ChallengeBattleManager::IsProc() const {
    return pad_26 != 0;
}

void ChallengeBattleManager::NotifyStartTelop() {
    TalkManager::get()->PlayNarrationVoice(TalkManager::NARRATION_TYPE(0x30), 0, 0);
    pad_1c = 2.75f;
}

void ChallengeBattleManager::Retry() {
    if (pad_26 == 0) {
        return;
    }
    if (pad_8 != nullptr) {
        pad_8->release();
        pad_8 = nullptr;
    }
    pad_10 = 0.0f;
    pad_14 = 0.0f;
    pad_18 = 0.0f;
    pad_1c = 0.0f;
    gf::GfMenuReference::setBattleTime(0.0f);
    pad_20 = 0;
    pad_22 = 0;
    DataManager::get()->SetPartyGauge(0, false);
    gf::GfMenuObjBtlTime::reset();
    pad_24 = 0;
    pad_28 = 0;
    pad_29 = 4;
    pad_2a = 0;
    pad_2b = 0;
    pad_2c = 0;
    pad_2d = 0;
    pad_20 = gmk::GmkBattleChallenge::sm_battleStatus.m_waveNum;
    pad_22 = gmk::GmkBattleChallenge::sm_battleStatus.m_waveIndex;
    pad_26 = 1;
}

void ChallengeBattleManager::PreUpdate(const fw::UpdateInfo&) {
    ChallengeBattleManager* self = get();
    if (self->pad_26 == 0) {
        return;
    }
    int prev = self->pad_22;
    self->pad_20 = gmk::GmkBattleChallenge::sm_battleStatus.m_waveNum;
    self->pad_22 = gmk::GmkBattleChallenge::sm_battleStatus.m_waveIndex;
    if (self->pad_22 > prev) {
        if (self->pad_22 >= 2) {
            BattleGlobal::get()->Tutorial(BTL_TUTORIAL_COND(0x12), 0, nullptr);
        }
        CharacterManager::get()->NotifyChallengeNextWave();
    }
    gf::ArenaMenuInfo* info = gf::GfGameManager::getBattleArenaMenuInfo();
    self->pad_29 = info->m_kind;
    self->pad_2a = info->m_id;
}

void ChallengeBattleManager::Update(const fw::UpdateInfo& info) {
    ChallengeBattleManager::get()->UpdateProc(info);
}

// whether a pause, a combo or special attack camera direction or a chain attack holds the challenge's progress (the
// checks CheckChallengeFailure makes too; the name is not the original's)
static inline bool IsProgressHeld() {
    if (BattleGlobal::get()->IsPause(-1)) {
        return true;
    }
    if (BattleGlobal::get()->m_uniteComboCamera || BattleGlobal::get()->pad_bit12 ||
        BattleGlobal::get()->m_elementalCombo.m_camera || SpAttackManager::get()->m_camera) {
        return true;
    }
    return ChainAttackManager::get()->IsProc(false);
}

void ChallengeBattleManager::UpdateProc(const fw::UpdateInfo& info) {
    unsigned char state = pad_26;
    unsigned char next = state;
    bool operate = true;
    bool suspend = false;
    switch (state) {
    case 0:
        return;
    case 1:
        DataManager::get()->RegisterUpdateAttackParam(true, false);
        gf::GfMenuObjBtlTime::openFromChallengeBattle();
        operate = false;
        pad_10 = 0.0f;
        next = 2;
        pad_2c = false;
        pad_2d = false;
        break;
    case 2:
        pad_10 = 0.0f;
        pad_2c = false;
        pad_2d = false;
        operate = false;
        if (gf::GfGameManager::isFadeClear()) {
            next = 3;
        }
        break;
    case 3:
        pad_10 = 0.0f;
        pad_2c = false;
        pad_2d = false;
        operate = false;
        next = gf::GfGameArena::get()->m_msgObj->pad_98 ? 51 : 3;
        break;
    case 51:
        if (CheckChallengeFailure()) {
            next = 151;
            break;
        }
        if (pad_29 == 2) {
            if (!CharacterManager::get()->IsExistChallengeBattleEnemy()) {
                next = 157;
            }
        } else if (pad_29 == 3) {
            int need = (unsigned short)Bdat::getValCheck(gf::GfDataBdat::getFP(77), "NeedDefeat", pad_2a, 2);
            int score = IsProc() ? gf::GfGameManager::getBattleArenaScore() : 0;
            if (score >= need) {
                next = 157;
            }
        } else if (!CharacterManager::get()->IsExistChallengeBattleEnemy()) {
            next = gmk::GmkBattleChallenge::sm_battleStatus.m_isEnd ? 157 : 101;
        }
        break;
    case 101:
        if (CheckChallengeFailure()) {
            next = 151;
        } else {
            suspend = true;
            next = 102;
        }
        break;
    case 102:
        suspend = true;
        if (CheckChallengeFailure()) {
            next = 151;
            break;
        }
        next = 103;
        if (pad_14 < 10.0f) {
            for (int i = 0; i < 20; i++) {
                const BattleCharacter* character = CharacterManager::get()->GetCharacterConst(i);
                if (character != nullptr && character->IsDead(0)) {
                    next = 102;
                    break;
                }
            }
        }
        break;
    case 103: {
        suspend = true;
        if (CheckChallengeFailure()) {
            next = 151;
            break;
        }
        CharacterManager* manager = CharacterManager::get();
        next = 104;
        for (int i = 0; i < 20; i++) {
            const BattleCharacter* character = manager->GetCharacterConst(i);
            if (character != nullptr && character->IsBattle()) {
                BattleCharacter* control = manager->GetControlCharacter();
                if ((control != nullptr && !control->IsBattle() && pad_14 >= 5.0f) || pad_14 >= 10.0f) {
                    next = 104;
                } else {
                    next = 103;
                }
                break;
            }
        }
        break;
    }
    case 104:
        if (CheckChallengeFailure()) {
            next = 151;
        } else if (CharacterManager::get()->IsExistBattleEnemy(nullptr, reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1),
                                                                false)) {
            next = 51;
        } else if (gmk::GmkBattleChallenge::sm_battleStatus.m_isEnd && pad_14 >= 5.0f) {
            next = 157;
        }
        break;
    case 151: {
        operate = false;
        if (IsProgressHeld()) {
            break;
        }
        gf::GfMenuCallContext* context = pad_8;
        if (context != nullptr) {
            context->reset();
        } else {
            context = gf::GfMenuCallContext::create();
            pad_8 = context;
        }
        if (context != nullptr) {
            gf::GfMenuObjBtlchTelop::OpenParam param;
            param.m_type = 3;
            param.m_value = pad_2d ? 2 : 1;
            gf::GfMenuObjBtlchTelop::open(pad_8, param);
        }
        gf::SCOM_BATTLE_ARENA::createPlayJingle(130, 1.0f, 0.2f);
        DropLoseEtherCube();
        gf::SCOM_BATTLE_ARENA::createLoseStart();
        next = 152;
        break;
    }
    case 152: {
        operate = false;
        if (IsProgressHeld()) {
            break;
        }
        float time = pad_14;
        gf::GfMenuCallContext* context = pad_8;
        bool closed = context == nullptr;
        if (time < 2.5f || !closed) {
            if (time <= 3.5f) {
                break;
            }
            if (!closed) {
                context->release();
                pad_8 = nullptr;
            }
        }
        next = 153;
        break;
    }
    case 153:
        operate = false;
        if (IsProgressHeld()) {
            break;
        }
        BattleGlobal::get()->Tutorial(BTL_TUTORIAL_COND(15), 0, nullptr);
        next = 154;
        break;
    case 154:
        operate = false;
        if (IsProgressHeld() || BattleGlobal::get()->pad_bit43 || UIManager::get()->m_tutorials.size() != 0 ||
            UIManager::get()->pad_e0 > 0.0f) {
            break;
        }
        if (pad_28 != 0) {
            next = 156;
            break;
        }
        TalkManager::get()->PlayNarrationVoice(TalkManager::NARRATION_TYPE(0x30), 3, 0);
        gf::GfMenuManager::openCommonWindow(280);
        next = 155;
        break;
    case 155:
        operate = false;
        if (gf::GfMenuManager::isOpenCommonWindow()) {
            break;
        }
        pad_28 = (unsigned short)gf::GfMenuManager::getCommonWindowResult() == 0 ? 2 : 1;
        // fall through
    case 156:
        operate = false;
        next = 156;
        if (IsProgressHeld() || !Utility::IsEnableEventStart()) {
            break;
        }
        gf::GfMenuObjBtlTime::closeAll();
        if (pad_28 == 2) {
            gf::SCOM_BATTLE_ARENA::createRetry();
            next = 201;
        } else if (pad_28 == 3) {
            gf::SCOM_BATTLE_ARENA::createGiveUp();
            next = 202;
        } else {
            gf::SCOM_BATTLE_ARENA::createLose();
            next = 202;
        }
        break;
    case 157: {
        unsigned int time = pad_10;
        time = time < 5999 ? time : 5999;
        gf::GfMenuObjSalvage::setBtlchNewRecord(time < gf::GfGameManager::getBattleArenaMenuInfo()->m_rule.m_value0);
        gf::SCOM_CLEAR_TIME::create(time);
        next = 158;
        break;
    }
    case 158: {
        if (IsProgressHeld()) {
            break;
        }
        BattleGlobal::get()->Tutorial(BTL_TUTORIAL_COND(16), 0, nullptr);
        gf::GfMenuCallContext* context = pad_8;
        if (context != nullptr) {
            context->reset();
        } else {
            context = gf::GfMenuCallContext::create();
            pad_8 = context;
        }
        if (context != nullptr) {
            gf::GfMenuObjBtlchTelop::OpenParam param;
            param.m_type = 3;
            param.m_value = 0;
            gf::GfMenuObjBtlchTelop::open(pad_8, param);
        }
        TalkManager::get()->PlayNarrationVoice(TalkManager::NARRATION_TYPE(0x30), 2, 0);
        gf::SCOM_BATTLE_ARENA::createPlayJingle(113, 1.0f, 0.2f);
        next = 159;
        break;
    }
    case 159: {
        if (IsProgressHeld()) {
            break;
        }
        float time = pad_14;
        gf::GfMenuCallContext* context = pad_8;
        bool closed = context == nullptr;
        if (time < 2.5f || !closed) {
            if (time <= 3.5f) {
                break;
            }
            if (!closed) {
                context->release();
                pad_8 = nullptr;
            }
        }
        next = 160;
        break;
    }
    case 160: {
        if (pad_18 < BtlSystemBalanceAccess::get()->pad_120 || IsProgressHeld() || !Utility::IsEnableEventStart()) {
            break;
        }
        gf::GfMenuObjBtlTime::closeAll();
        UIManager* ui = UIManager::get();
        ui->pad_30 = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
        ui->pad_38 = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
        ui->pad_40 = 0;
        ui->pad_41 = 0;
        next = 161;
        break;
    }
    case 161:
        gf::SCOM_BATTLE_ARENA::createWin();
        next = 202;
        break;
    }
    if (BattleGlobal::get()->IsPause(-1) || ChainAttackManager::get()->IsProc(false) || pad_26 >= 150) {
        suspend = true;
    }
    gmk::GmkBattleChallenge::suspend(suspend);
    pad_2b = operate && pad_26 < 200;
    bool pause = BattleGlobal::get()->IsPause(-1);
    if (!pause && next >= 50 && next < 150) {
        float time = pad_10 + info.m_frameTime;
        float limit = gf::GfGameManager::getBattleArenaMenuInfo()->m_value4;
        pad_10 = time < limit ? time : limit;
    }
    if (next == state) {
        pad_14 += info.m_frameTime;
        pad_18 += info.m_deltaTime;
    } else {
        pad_14 = 0.0f;
        pad_18 = 0.0f;
    }
    pad_26 = next;
    if (pad_1c > 0.0f) {
        pad_1c -= info.m_deltaTime;
        if (pad_1c <= 0.0f) {
            TalkManager::get()->PlayNarrationVoice(TalkManager::NARRATION_TYPE(0x30), 1, 0);
            BattleGlobal::get()->Tutorial(BTL_TUTORIAL_COND(13), 0, nullptr);
            if (pad_29 >= 1 && pad_29 <= 3) {
                BattleGlobal::get()->Tutorial(BTL_TUTORIAL_COND(pad_29 + 0x12), 0, nullptr);
            }
        }
    }
    RetireProc(info);
    if (pad_26 < 150) {
        unsigned short id = pad_24;
        unsigned short current = BattleGlobal::get()->pad_8374[30];
        if (id == 0) {
            if (current != 0) {
                pad_24 = current;
                goto bgm_done;
            }
            CharacterManager::get()->SetupBGM(false, false);
            id = BattleGlobal::get()->pad_83b2;
            pad_24 = id;
            current = id;
        }
        if (pad_24 != 0 && current == 0) {
            BattleGlobal::get()->SetBGM(id);
        }
    }
bgm_done:
    if (pad_8 != nullptr && pad_8->isTerm()) {
        if (pad_8 != nullptr) {
            pad_8->release();
            pad_8 = nullptr;
        }
    }
}

bool ChallengeBattleManager::CheckChallengeFailure() const {
    if (pad_2c != 0) {
        return true;
    }
    if (BattleGlobal::get()->IsPause(-1)) {
        return false;
    }
    if (BattleGlobal::get()->m_uniteComboCamera || BattleGlobal::get()->pad_bit12 ||
        BattleGlobal::get()->m_elementalCombo.m_camera || SpAttackManager::get()->m_camera) {
        return false;
    }
    if (ChainAttackManager::get()->IsProc(false)) {
        return false;
    }
    if (BattleGlobal::get()->IsGameOver()) {
        pad_2c = true;
        return true;
    }
    if (pad_2d != 0) {
        return false;
    }
    float limit = gf::GfGameManager::getBattleArenaMenuInfo()->m_value4;
    if (pad_10 >= limit) {
        pad_2c = true;
        pad_2d = true;
        return true;
    }
    return false;
}

bool ChallengeBattleManager::IsWaveFinished() const {
    return gmk::GmkBattleChallenge::sm_battleStatus.m_isEnd;
}

void ChallengeBattleManager::DropLoseEtherCube() {
    if (gf::GfGameManager::getBattleArenaMenuInfo()->m_ratios[1] <= 0.0f) {
        return;
    }
    BattleCharacter* character = CharacterManager::get()->GetControlCharacter();
    if (character == nullptr) {
        return;
    }
    const CharacterParameter* param = character->GetCharacterParameterConst(true);
    if (param == nullptr) {
        return;
    }
    mm::Vec3 pos = character->m_pos;
    pos.y += param->pad_38;
    float angle = (ml::mtRandf1() - 0.5f) * 6.2831855f;
    float range = ml::mtRandf1() * 3.14159274f;
    range = fminf(fmaxf(range, 5.23598766f), 3.14159274f);
    gf::GfFobjDropitem::EmitInfo info;
    info.m_pos = pos;
    info.m_items.setAllocator(fw::FrameworkMemory::getAllocator(5));
    info.m_items.reserve(1);
    info.m_paramId = 0;
    info.m_angle = angle;
    info.m_angleRange = range;
    gf::GfDropitemInfo item;
    item.pad_0x0 = 0;
    item.pad_0x4 = 10;
    item.pad_0x5 = 100;
    item.pad_0x8 = 0;
    item.pad_0xc = 10;
    item.pad_0x10 = 0.0f;
    info.m_items.push_back(item);
    gf::GfFobjDropitem::emitDropitems(info);
}

bool ChallengeBattleManager::IsResult() const {
    return pad_26 > 149;
}

bool ChallengeBattleManager::IsExit() const {
    return pad_26 > 199;
}

void ChallengeBattleManager::RetireProc(const fw::UpdateInfo&) {
    int step = pad_27;
    switch (step) {
    case 0:
        if (pad_26 >= 50 && pad_26 < 150 && (fw::PadManager::getControlPadData(0).m_down & 0x200)) {
            BattleCharacter* character = CharacterManager::get()->GetControlCharacter();
            if ((character != nullptr && character->IsBattle()) || DataManager::get()->IsExistRequestPermit() ||
                BattleGlobal::get()->m_uniteComboCamera || BattleGlobal::get()->pad_bit12 ||
                BattleGlobal::get()->m_elementalCombo.m_camera || SpAttackManager::get()->m_camera ||
                BladeChangeManager::get()->IsProcDisableCancel(reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) ||
                BladeChangeManager::get()->IsProcKakusei() || BattleGlobal::get()->IsPause(-1)) {
                BattleGlobal::get()->PlayErrorSE();
            } else {
                BattleGlobal::get()->SetPause(7, true);
                step = 1;
                gf::GfMenuManager::openCommonWindow(290);
            }
        }
        break;
    case 1:
        if (!(pad_26 >= 50 && pad_26 < 150)) {
            gf::GfMenuManager::closeCommonWindow();
        } else {
            if (gf::GfMenuManager::isOpenCommonWindow()) {
                break;
            }
            switch ((unsigned short)gf::GfMenuManager::getCommonWindowResult()) {
            case 0:
                pad_28 = 3;
                pad_26 = 153;
                break;
            case 2:
                pad_28 = 2;
                pad_26 = 153;
                break;
            }
        }
        BattleGlobal::get()->SetPause(7, false);
        step = 0;
        break;
    }
    pad_27 = step;
}

void ChallengeBattleManager::SetBGMID(unsigned int value) {
    if (pad_26 != 0) {
        pad_24 = value;
    }
}

void ChallengeBattleManager::AddScoreByID(int id, BattleCharacter* character) {
    if (pad_26 == 0) {
        return;
    }
    AddScore((unsigned short)Bdat::getValCheck(gf::GfDataBdat::getFP(78), "Score", id, 2), false);
    if (character != nullptr) {
        character->DropEtherCubeByScoreID(id);
    }
}

void ChallengeBattleManager::AddScore(int score, bool always) {
    if (pad_26 == 0) {
        return;
    }
    bool limited = (pad_29 >= 2 && pad_29 <= 3) && !always;
    if (score == 0) {
        return;
    }
    if (limited) {
        return;
    }
    gf::SCOM_ADD_SCORE::create(score);
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
