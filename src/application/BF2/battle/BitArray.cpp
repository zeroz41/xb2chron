#include "btl/Utility.h"
#include "btl/Misc.h"
#include "btl/challenge_battle_manager.h"
#include "btl/siren_battle_manager.h"
#include "classes/btl/ShakeCameraManager.h"
#include "classes/gf/GfSmnEnemyManager.h"
#include "btl/formation_change_manager.h"
#include "classes/btl/BattleCharacter.h"
#include "classes/btl/BattleGlobal.h"
#include "classes/btl/BladeChangeManager.h"
#include "classes/btl/BladeArtsManager.h"
#include "classes/btl/BtlSystemBalanceAccess.h"
#include "classes/btl/ChainAttackManager.h"
#include "classes/btl/CharacterManager.h"
#include "classes/btl/DataManager.h"
#include "classes/btl/SpAttackManager.h"
#include "classes/btl/TalkManager.h"
#include "classes/gf/GfGameCond.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfGameParty.h"
#include "gf/GfDataBlade.h"
#include "gf/GfGameUtil.h"
#include "gf/GfObjUtil.h"
#include "classes/btl/CharacterParameter.h"
#include "classes/gf/SCOM_ENBOOK_BOSS_TIME.h"
#include "classes/gf/SCOM_ENBOOK_DEAD_PLAYER.h"
#include "classes/gf/SCOM_ENBOOK_DEFEAT_ENEMY.h"
#include "classes/gf/SCOM_ENBOOK_IN_BATTLE.h"
#include "mm/mtl/FixedVector.h"
#include "gf/GfDataDriver.h"
#include "classes/btl/UIManager.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/GfObj.h"
#include "classes/gf/GfComPropertyPc.h"
#include "gf/GfTargetProperty.h"
#include "classes/gf/GfDataBdat.h"
#include "plugin/Bdat.h"
#include "mm/mtl/FixStr.h"
#include <string.h>
#include "ml/MTRand.h"
#include "classes/gf/SCOM_ACHIEV_INC.h"
#include <stdlib.h>

namespace btl {

void Utility::StartChallengeBattleCallback() {
    ChallengeBattleManager::sys()->Start();
}

void Utility::EndChallengeBattleCallback() {
    ChallengeBattleManager::sys()->End();
}

void Utility::RetryChallengeBattleCallback() {
    ChallengeBattleManager::sys()->Retry();
}

void Utility::ChallengeBattleStartTelopCallback() {
    ChallengeBattleManager::sys()->NotifyStartTelop();
}

bool Utility::IsPause() {
    BattleGlobal* global = BattleGlobal::sys();
    if (global->IsPause(-1)) {
        return true;
    }
    return global->pad_a50 <= 0.0f;
}

bool Utility::IsBanOperateForField() {
    return !(ChallengeBattleManager::sys()->IsEnableOperate() && SirenBattleManager::sys()->IsEnableOperate());
}

bool Utility::IsEnablePreciousDrop() {
    if (BattleGlobal::sys()->IsPause(-1)) {
        return false;
    }
    if (BattleGlobal::sys()->m_buttonChallenge.IsProc()) {
        return false;
    }
    if (ChainAttackManager::sys()->IsProc(true)) {
        return false;
    }
    return !BattleGlobal::sys()->IsFutureView();
}

gf::GF_OBJ_HANDLE* Utility::GetLeader() {
    return gf::GfGameManager::getPartyLeaderDriver();
}

gf::GF_OBJ_HANDLE* Utility::GetControlCharacterHandle() {
    ChainAttackManager* chain = ChainAttackManager::sys();
    if (chain->IsProc(false)) {
        int group = ChainAttackManager::sys()->GetGroupIndex();
        if (group >= 0) {
            return gf::GfGameParty::getHandleDriver(group, static_cast<gf::PTPOS>(0));
        }
    }
    return gf::GfGameManager::getPartyLeaderDriver();
}

bool Utility::IsSatisfyCondition(int condition) {
    if (condition != 2 || ChallengeBattleManager::sys()->pad_29 != 3) {
        BattleGlobal* global = BattleGlobal::sys();
        const char* column;
        if (global->m_challengeAnySuccess) {
            if ((1 << condition) & 0xBBF9) {
                return false;
            }
            column = "FLD_CondID2";
            if (((1 << condition) & 0xF0006) && global->pad_bit42) {
                return true;
            }
        } else {
            if (global->pad_bit42) {
                if ((1 << condition) & 0x8CCE7) {
                    return true;
                }
                if ((1 << condition) & 0x18) {
                    return false;
                }
            }
            column = "FLD_CondID";
        }
        unsigned short id = Bdat::getValCheckU16(gf::GfDataBdat::getFP(0x1E), column, condition);
        if (id != 0) {
            return gf::GfGameCond::isGameCond(id);
        }
    }
    return false;
}

bool Utility::IsSatisfyConditionFld(int condition) {
    return gf::GfGameCond::isGameCond(condition);
}

void Utility::AchieveCondition(BTL_ACHIEVE_COND cond, gf::GF_OBJ_HANDLE* handle, unsigned int value) {
    switch (cond) {
    case 0:
        gf::SCOM_ACHIEV_INC::createBladeArts(handle, value);
        break;
    case 1:
        gf::SCOM_ACHIEV_INC::createBladeArtsSp(handle, value);
        break;
    case 2:
        gf::SCOM_ACHIEV_INC::createBladeNArts(handle);
        break;
    case 3:
        gf::SCOM_ACHIEV_INC::createKizuna(handle);
        break;
    case 4:
        gf::SCOM_ACHIEV_INC::createFightCombo(handle);
        break;
    case 5:
        gf::SCOM_ACHIEV_INC::createDriverCombo2(handle);
        break;
    case 6:
        gf::SCOM_ACHIEV_INC::createFightComboFinish(handle);
        gf::SCOM_ACHIEV_INC::createDriverCombo4(handle);
        break;
    case 7:
        gf::SCOM_ACHIEV_INC::createElementalCombo(handle);
        break;
    case 8:
        gf::SCOM_ACHIEV_INC::createBladeCombo2(handle);
        break;
    case 9:
        gf::SCOM_ACHIEV_INC::createElementalComboFinish(handle);
        gf::SCOM_ACHIEV_INC::createBladeCombo3(handle);
        break;
    case 10:
        gf::SCOM_ACHIEV_INC::createFusionCombo(handle);
        break;
    case 11:
        gf::SCOM_ACHIEV_INC::createChainAttack(handle);
        break;
    case 12:
        gf::SCOM_ACHIEV_INC::createButtonChallenge();
        break;
    case 13:
        gf::SCOM_ACHIEV_INC::createHelp(handle);
        break;
    case 14:
        gf::SCOM_ACHIEV_INC::createPotGet();
        break;
    case 15:
        gf::SCOM_ACHIEV_INC::createAvoid(handle);
        break;
    case 16:
        gf::SCOM_ACHIEV_INC::createGuard(handle);
        break;
    case 17:
        gf::SCOM_ACHIEV_INC::createBladeChange(handle);
        break;
    case 18:
        gf::SCOM_ACHIEV_INC::createRecover(handle, value);
        break;
    case 19:
        gf::SCOM_ACHIEV_INC::createBackAttack(handle);
        break;
    case 20:
        gf::SCOM_ACHIEV_INC::createOverKill();
        break;
    }
}

void Utility::NotifyDead(gf::GF_OBJ_HANDLE* handle, const gf::MsgObjectNotifyDead& msg) {
    BattleCharacter* character = CharacterManager::sys()->GetCharacterConst(handle);
    if (character) {
        character->NotifyDead(msg);
    }
}

void Utility::NotifyNeedPutAwayWeapon() {
    BattleGlobal::sys()->pad_bit7 = true;
}

void Utility::GetArtsData(ARTS_DATA::DATA_TYPE type, int id, ARTS_DATA& data) {
    DataManager::sys()->GetArtsData(type, id, data);
}

unsigned short Utility::GetArtsEnhance(const ARTS_DATA& data, int index) {
    return data.m_enhances[index - 1].id;
}

int Utility::GetSeType(const char* name) {
    if (name == nullptr || *name == '\0') {
        return 0;
    }
    unsigned char* fp = gf::GfDataBdat::getFP(0x3B);
    int id = Bdat::getIdTop(fp);
    int count = Bdat::getIdCount(fp);
    if (count > 0) {
        int end = count + id;
        do {
            const char* pack = reinterpret_cast<const char*>(Bdat::getValCheck(fp, "PackName", id, 7));
            if (pack && strcmp(pack, name) == 0) {
                return id;
            }
            id++;
        } while (id < end);
    }
    return 0;
}

namespace {
// the SE type each weapon type sounds (types 1-49; the name is not the original's)
const unsigned short s_weaponSeType[49] = {
    0xC, 0xD, 0xE, 0xF, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C,
    0x1D, 0x1E,
};
// the SE type each attribute sounds (attributes 1-8; the name is not the original's)
const unsigned short s_attrSeType[8] = {4, 5, 6, 7, 8, 9, 10, 11};
}  // namespace

int Utility::GetWeaponSeType(int weaponType) {
    if (weaponType >= 1 && weaponType <= 49) {
        return s_weaponSeType[weaponType - 1];
    }
    return 0;
}

int Utility::GetAttrSeType(int attr) {
    if (attr >= 1 && attr <= 8) {
        return s_attrSeType[attr - 1];
    }
    return 0;
}

int Utility::GetAntiAttribute(unsigned int attr) {
    // Proposed name, not the original's: the symbols leave it unnamed (lbl_71009B5BBE)
    static const signed char s_antiAttribute[] = {-1, 2, 1, 6, 5, 4, 3, 8, 7};
    if (attr > 8) {
        return -1;
    }
    return s_antiAttribute[attr];
}

int Utility::GetElementalEffectID() {
    return DataManager::sys()->m_elementalEffectID;
}

namespace {
// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100B3A800). The kizuna ranks' column
// suffixes, by rank - 1.
const char* const s_kizunaRankName[] = {"E",  "D",  "C",  "B",  "A",  "S",  "S1", "S2",
                                        "S3", "S4", "S5", "S6", "S7", "S8", "S9", "SS"};
}  // namespace

void Utility::GetFluctuateKizunaData(KIZUNA_FLUCTUATE& data, int id, int rank) {
    unsigned char* fp = gf::GfDataBdat::getFP(0xB);
    mm::mtl::FixStr<32> column;
    data.m_value = static_cast<short>(Bdat::getValCheck(fp, column.format("Param%s", s_kizunaRankName[rank - 1]).m_str, id, 5));
    bool target = Bdat::getValCheckU8(fp, "Target", id) == 1;
    data.m_target = target;
    if (target && ((1 << id) & 0x3808) && ChainAttackManager::sys()->IsProc(true)) {
        data.m_target = false;
    }
}

int Utility::GetUniteComboID(int first, int second) {
    if (first == 0 || second == 0) {
        return 0;
    }
    int stage = BattleGlobal::sys()->GetElementalComboStage(second) + first;
    if (stage < 2) {
        return 0;
    }
    return stage - 1;
}

int Utility::GetDamageAttackerType(gf::GF_OBJ_HANDLE* object, gf::GF_OBJ_HANDLE* attacker, bool flag) {
    BattleCharacter* character = CharacterManager::sys()->GetCharacterConst(attacker);
    if (character) {
        if (!character->m_isPlayer) {
            return 0;
        }
        return character->IsControlCharacterGroup() ? 2 : 1;
    }
    bool isEnemy = gf::GfObjUtil::getObjType(object) == 5;
    if (flag) {
        return isEnemy ? 0 : 2;
    }
    return isEnemy ? 2 : 0;
}

void Utility::PickupEtherCube(int value, gf::GF_OBJ_HANDLE*) {
    ChallengeBattleManager::sys()->AddEtherCube(value);
}

float Utility::GetDyingHpRate() {
    return BtlSystemBalanceAccess::sys()->m_dyingHpRate;
}

unsigned int Utility::GetTrustRank(int blade) {
    return gf::GfDataBlade::getTrustRank(blade);
}

unsigned int Utility::GetIraDummyBladeID(unsigned int blade) {
    return gf::GfDataDriver::getIraBlade(GetIraGroupDriverID(blade), GetIraBladeSlot(blade));
}

void Utility::FullCoolTime() {
    DataManager::sys()->pad_15D1A = 1;
}

void Utility::SetBattleEndEnemyCall(float value) {
    BattleGlobal::sys()->pad_5dd8 = value;
}

void Utility::SetPlayerKizunaStage(int stage, bool engagedOnly) {
    DataManager::sys()->SetKizunaStage(stage, engagedOnly);
}

bool Utility::IsEnableFieldBladeChange() {
    BattleCharacter* leader = CharacterManager::sys()->GetCharacterConst(gf::GfGameManager::getPartyLeaderDriver());
    if (leader && leader->IsBattle() && leader->m_state != 3) {
        return false;
    }
    if (!TalkManager::sys()->IsEnableFieldBladeChange()) {
        return false;
    }
    if (BattleGlobal::sys()->m_challengeAnySuccess && FormationChangeManager::sys()->m_count > 0) {
        return false;
    }
    return true;
}

void Utility::EntangleEnemy(gf::GF_OBJ_HANDLE* handle, float radius, int group) {
    gf::GfSmnEnemyManager::AbsSmnInfo info;
    info.handle = handle;
    info.flagBit = 0;
    info.radius = radius;
    info.group = group;
    gf::GfSmnEnemyManager::execAbsSummon(info);
}

bool Utility::IsEnableDeadSequence() {
    return !TalkManager::sys()->IsPlayingEnemyWinVoice();
}

bool Utility::IsThirdCharacter(gf::GF_OBJ_HANDLE* handle) {
    return gf::GfObjUtil::isTrinityBlade(handle);
}

bool Utility::IsBladeArtsBuff(int buff) {
    return buff >= 1 && buff <= 9;
}

bool Utility::IsForward(gf::GF_OBJ_HANDLE* handle) {
    if (handle == reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        return false;
    }
    for (unsigned int group = 0; group < 3; group++) {
        if (gf::GfGameParty::getHandleDriver(group, static_cast<gf::PTPOS>(0)) == handle) {
            return true;
        }
    }
    return false;
}

int Utility::GetIraGroupDriverID(unsigned int blade) {
    switch (blade) {
    case 17: return 17;
    case 18: return 18;
    case 19: return 19;
    case 20: return 17;
    case 21: return 17;
    case 22: return 18;
    case 23: return 18;
    default: return 19;
    }
}

int Utility::GetIraBladeSlot(unsigned int blade) {
    switch (blade) {
    case 20: return 0;
    case 21: return 1;
    case 22: return 0;
    case 23: return 1;
    case 24: return 0;
    case 25: return 1;
    default: return -1;
    }
}

bool Utility::IsEnableEnemyBattle() {
    if (BattleGlobal::sys()->IsEnableBattle()) {
        return ChallengeBattleManager::sys()->IsEnableEnemyBattle();
    }
    return false;
}

bool Utility::IsBattleAutoHeal() {
    return ChallengeBattleManager::sys()->IsEnableAutoHeal();
}

bool Utility::IsCharacterAutoHeal(gf::GF_OBJ_HANDLE* handle) {
    BattleCharacter* character = CharacterManager::sys()->GetCharacterConst(handle);
    if (character) {
        return character->IsAutoHeal();
    }
    return true;
}

void Utility::SomebodyPraise(int id, bool flag, bool finish) {
    CharacterManager* manager = CharacterManager::sys();
    BattleCharacter* chr = manager->GetCharacterConst(id);
    if (chr == nullptr) {
        return;
    }
    const CharacterParameter* param = chr->GetCharacterParameterConst(true);
    if (param == nullptr) {
        return;
    }
    BattleCharacter* speakers[5];
    int num = 0;
    if (!flag && !finish && !param->m_flags622_6) {
        BattleCharacter* driver = manager->GetCharacterConst(param->m_driverHandle);
        if (driver && driver->IsEnableSpeakVoice(false)) {
            speakers[num++] = driver;
        }
    }
    if (param->IsPlayerParameter()) {
        int group = param->m_groupIndex;
        for (int i = 0; i < 3; i++) {
            if (i == group) {
                continue;
            }
            BattleCharacter* other = manager->GetCharacterConst(gf::GfGameParty::getHandleDriver(i, static_cast<gf::PTPOS>(0)));
            if (other && other->IsEnableSpeakVoice(false)) {
                speakers[num++] = other;
            }
        }
    }
    if (num != 0) {
        BattleCharacter* speaker = num != 1 ? speakers[ml::mtRand(num)] : speakers[0];
        if (finish) {
            TalkManager::sys()->NotifyTrigger(speaker->m_voiceIndex, static_cast<TalkManager::TRIGGER>(0x2D), 0, 0);
        } else {
            TalkManager::sys()->NotifyTrigger(speaker->m_voiceIndex, static_cast<TalkManager::TRIGGER>(0x12), 0, 0);
        }
    }
}

void Utility::RegisterEnemyBook(ENBOOK_TYPE type, gf::GF_OBJ_HANDLE* handle, int value) {
    switch (type) {
    case 0:
        gf::SCOM_ENBOOK_IN_BATTLE::create(handle);
        break;
    case 1:
        gf::SCOM_ENBOOK_BOSS_TIME::create(handle, value);
        break;
    case 2:
        gf::SCOM_ENBOOK_DEFEAT_ENEMY::create(handle);
        break;
    case 3:
        gf::SCOM_ENBOOK_DEAD_PLAYER::create(handle);
        break;
    }
}

int Utility::AI_GetCharacterAIID(gf::GF_OBJ_HANDLE* handle) {
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
    if (chr) {
        return chr->GetAiChrID();
    }
    return -1;
}

gf::GF_OBJ_HANDLE* Utility::AI_GetCharacterHandle(int id) {
    if (id >= 0) {
        bool isPlayer;
        if (static_cast<unsigned int>(id) < 16) {
            isPlayer = true;
        } else if (id >= 100 && id <= 168) {
            id -= 100;
            isPlayer = false;
        } else {
            return reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
        }
        int index = CharacterManager::sys()->GetCharacterIDByAiChrID(id, isPlayer);
        if (index >= 0) {
            BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(index);
            if (chr) {
                return chr->m_handle;
            }
        }
    }
    return reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
}

bool Utility::AI_IsValidID(int id) {
    return AI_GetCharacterHandle(id) != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
}

bool Utility::AI_GetObjectPosition(gf::GF_OBJ_HANDLE* handle, mm::Vec3& pos) {
    return Misc::GetObjectTransform(handle, pos, Misc::TRANS_TYPE_POS);
}

int Utility::AI_GetTargetCharacterID(gf::GF_OBJ_HANDLE* handle) {
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
    if (chr && chr->m_targetHandle != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        BattleCharacter* target = CharacterManager::sys()->GetCharacterConst(chr->m_targetHandle);
        if (target) {
            return target->GetAiChrID();
        }
    }
    return -1;
}

int Utility::AI_GetLinkCharacterID(gf::GF_OBJ_HANDLE* handle) {
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
    if (chr) {
        gf::GF_OBJ_HANDLE* link = BattleGlobal::sys()->GetLinkJoinEnemyHandle(chr->m_pos);
        if (link != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
            BattleCharacter* enemy = CharacterManager::sys()->GetCharacterConst(link);
            if (enemy) {
                return enemy->GetAiChrID();
            }
        }
    }
    return -1;
}

bool Utility::AI_IsFly(gf::GF_OBJ_HANDLE* handle) {
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
    if (chr) {
        return chr->m_isFly;
    }
    return false;
}

float Utility::AI_GetVertDiff(gf::GF_OBJ_HANDLE* handle, gf::GF_OBJ_HANDLE* target) {
    mm::Vec3 pos;
    mm::Vec3 targetPos;
    float diff = 3.40282347e+38f;
    if (Misc::GetObjectTransform(handle, pos, Misc::TRANS_TYPE_POS) &&
        Misc::GetObjectTransform(target, targetPos, Misc::TRANS_TYPE_POS)) {
        diff = targetPos.y - pos.y;
    }
    return diff;
}

int Utility::AI_GetEnemyNum() {
    int num = 0;
    for (int i = 20; i < 90; i++) {
        BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(i);
        if (chr && !chr->IsBackward() && !chr->IsDead(0)) {
            num += chr->IsBattle();
        }
    }
    return num;
}

int Utility::AI_GetPlayerNum() {
    int num = 0;
    for (int i = 0; i < 20; i++) {
        BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(i);
        if (chr && !chr->IsBackward() && !chr->IsDead(0)) {
            num += chr->IsBattle();
        }
    }
    return num;
}

int Utility::AI_GetAimCharacterNum(gf::GF_OBJ_HANDLE* handle) {
    int num = 0;
    mm::mtl::FixedVector<unsigned char, 90> list;
    if (GetCharacterList(list, handle, static_cast<CHECK_CHR_NUM_MODE>(0), 0x23) > 0) {
        CharacterManager* manager = CharacterManager::sys();
        for (unsigned char index : list) {
            if (manager->GetCharacterConst(index)->m_targetHandle == handle) {
                num++;
            }
        }
    }
    return num;
}

int Utility::AI_GetFightComboID(gf::GF_OBJ_HANDLE* handle) {
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
    if (chr) {
        return chr->GetCharacterParameterConst(true)->GetFightComboDataConst()->m_id;
    }
    return 0;
}

int Utility::AI_GetElementalComboID(gf::GF_OBJ_HANDLE* handle) {
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
    if (chr) {
        return chr->GetCharacterParameterConst(true)->m_elementalComboID;
    }
    return 0;
}

int Utility::AI_GetResistantAttrNum(gf::GF_OBJ_HANDLE* handle) {
    BattleCharacter* character = CharacterManager::sys()->GetCharacterConst(handle);
    if (character) {
        return Misc::GetFlagBitNum(character->GetCharacterParameterConst(true)->pad_5d8);
    }
    return 0;
}

int Utility::AI_GetReactionID(gf::GF_OBJ_HANDLE* handle) {
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
    if (chr) {
        return chr->m_reactionID;
    }
    return 0;
}

int Utility::AI_GetStamp(gf::GF_OBJ_HANDLE* handle) {
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
    if (chr && !chr->IsDead(0)) {
        return chr->m_stamp;
    }
    return 0;
}

int Utility::AI_GetStampCharacterID(int stamp) {
    for (int i = 0; i < 90; i++) {
        BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(i);
        if (chr == nullptr || chr->IsDead(0)) {
            continue;
        }
        if (chr->m_stamp == stamp) {
            return chr->GetAiChrID();
        }
    }
    return -1;
}

float Utility::AI_GetHpPercent(gf::GF_OBJ_HANDLE* handle) {
    float percent = 0.0f;
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
    if (chr && !chr->IsDead(0)) {
        const CharacterParameter* param = chr->GetCharacterParameterConst(true);
        if (param) {
            unsigned int hp = param->GetHP();
            unsigned int maxHp = param->GetMaxHP();
            if (maxHp != 0) {
                float now = hp;
                float max = maxHp;
                percent = now >= max ? 100.0f : now / max * 100.0f;
            }
        }
    }
    return percent;
}


int Utility::AI_GetLevel(gf::GF_OBJ_HANDLE* handle) {
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
    if (chr && !chr->IsDead(0)) {
        CharacterParameter* param = chr->GetCharacterParameterConst(true);
        if (param) {
            return param->GetLevel();
        }
    }
    return 0;
}

int Utility::AI_GetAttribute(gf::GF_OBJ_HANDLE* handle) {
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
    if (chr && !chr->IsDead(0)) {
        CharacterParameter* param = chr->GetCharacterParameterConst(true);
        if (param) {
            return param->GetAttribute();
        }
    }
    return 0;
}

int Utility::AI_GetRescueTargetCharacterID(gf::GF_OBJ_HANDLE* handle) {
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
    if (chr) {
        gf::GF_OBJ_HANDLE* target = chr->GetRescueTarget();
        if (target != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
            BattleCharacter* targetChr = CharacterManager::sys()->GetCharacterConst(target);
            if (targetChr) {
                return targetChr->GetAiChrID();
            }
        }
    }
    return -1;
}

int Utility::AI_GetBackAttackerCharacterID(gf::GF_OBJ_HANDLE* handle) {
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
    if (chr) {
        int index = chr->m_backAttacker;
        BattleCharacter* attacker = CharacterManager::sys()->GetCharacterConst(index);
        if (attacker) {
            return attacker->GetAiChrID();
        }
    }
    return -1;
}

bool Utility::AI_StartActionRescue(gf::GF_OBJ_HANDLE* handle, int target) {
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
    if (!chr) {
        return false;
    }
    if (BattleGlobal::sys()->m_challengeAnySuccess && !chr->IsForward()) {
        return false;
    }
    bool isPlayer;
    if (static_cast<unsigned int>(target) < 16) {
        isPlayer = true;
    } else if (target >= 100 && target <= 168) {
        target -= 100;
        isPlayer = false;
    } else {
        return false;
    }
    int index = CharacterManager::sys()->GetCharacterIDByAiChrID(target, isPlayer);
    if (index < 0) {
        return false;
    }
    if (!chr->IsProcAI(false)) {
        return false;
    }
    return chr->AI_Rescue(static_cast<BattleCharacter::ACTION_ID>(chr->m_state), index);
}

bool Utility::AI_StartActionEscape(gf::GF_OBJ_HANDLE* handle) {
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
    if (chr) {
        return chr->StartBackHome();
    }
    return false;
}

bool Utility::AI_StartActionArts(gf::GF_OBJ_HANDLE* handle, int slot, int target) {
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
    if (!chr) {
        return false;
    }
    if (BattleGlobal::sys()->m_challengeAnySuccess && !chr->IsForward()) {
        return false;
    }
    int index;
    if (target < 0) {
        index = -1;
    } else {
        bool isPlayer;
        if (static_cast<unsigned int>(target) < 16) {
            isPlayer = true;
        } else if (target >= 100 && target <= 168) {
            target -= 100;
            isPlayer = false;
        } else {
            return false;
        }
        index = CharacterManager::sys()->GetCharacterIDByAiChrID(target, isPlayer);
        if (index < 0) {
            return false;
        }
    }
    if (!chr->IsProcAI(false)) {
        return false;
    }
    if (chr->AI_Arts(static_cast<BattleCharacter::ACTION_ID>(chr->m_state), slot)) {
        chr->m_aiArtsTarget = index;
        return true;
    }
    return false;
}

bool Utility::AI_StartActionArtsByID(gf::GF_OBJ_HANDLE* handle, int id, int arg) {
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
    if (chr) {
        int slot = chr->GetArtsSlotIndex(id);
        if (slot >= 0) {
            return AI_StartActionArts(handle, slot, arg);
        }
    }
    return false;
}

bool Utility::AI_StartActionAttack(gf::GF_OBJ_HANDLE* handle) {
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
    if (!chr) {
        return false;
    }
    if (BattleGlobal::sys()->m_challengeAnySuccess && !chr->IsForward()) {
        return false;
    }
    if (!chr->IsProcAI(false)) {
        return false;
    }
    return chr->AI_Attack(static_cast<BattleCharacter::ACTION_ID>(chr->m_state), false);
}

bool Utility::AI_StartActionTalentArts(gf::GF_OBJ_HANDLE* handle) {
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
    if (!chr) {
        return false;
    }
    if (BattleGlobal::sys()->m_challengeAnySuccess && !chr->IsForward()) {
        return false;
    }
    if (!chr->IsProcAI(false)) {
        return false;
    }
    return chr->AI_Arts(static_cast<BattleCharacter::ACTION_ID>(chr->m_state), 7);
}

bool Utility::AI_StartActionBladeChange(gf::GF_OBJ_HANDLE* handle, int blade) {
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
    if (!chr) {
        return false;
    }
    if (BattleGlobal::sys()->m_challengeAnySuccess && !chr->IsForward()) {
        return false;
    }
    if (!chr->IsProcAI(false)) {
        return false;
    }
    return chr->AI_BladeChange(static_cast<BattleCharacter::ACTION_ID>(chr->m_state), blade);
}

bool Utility::AI_IsAngry(gf::GF_OBJ_HANDLE* handle) {
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
    if (chr) {
        return chr->IsAngry();
    }
    return false;
}

bool Utility::AI_SetAngry(gf::GF_OBJ_HANDLE* handle, float time) {
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
    if (chr) {
        return chr->SetAngry(true, time);
    }
    return false;
}

int Utility::AI_GetArtsEnemyNum() {
    int num = 0;
    for (int i = 20; i < 90; i++) {
        BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(i);
        if (chr && !chr->IsBackward() && !chr->IsDead(0) && chr->IsBattle()) {
            switch (chr->m_state) {
            case 7:
            case 9:
            case 12:
                num++;
                break;
            }
        }
    }
    return num;
}

int Utility::AI_GetArtsPlayerNum() {
    int num = 0;
    for (int i = 0; i < 20; i++) {
        BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(i);
        if (chr && !chr->IsBackward() && !chr->IsDead(0) && chr->IsBattle()) {
            switch (chr->m_state) {
            case 7:
            case 9:
            case 12:
                num++;
                break;
            }
        }
    }
    return num;
}

bool Utility::AI_TurnTarget(gf::GF_OBJ_HANDLE* handle) {
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
    if (chr && chr->IsEnableTurnAI()) {
        chr->TurnTarget(false, false, true);
        return true;
    }
    return false;
}

bool Utility::AI_TurnDirection(gf::GF_OBJ_HANDLE* handle, const mm::Vec3& dir) {
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
    if (chr && chr->IsEnableTurnAI()) {
        mm::Vec3 xz = dir;
        Misc::NormalizeXZ(xz);
        chr->TurnDirection(xz, false, true);
        return true;
    }
    return false;
}

void Utility::AI_SetUseNavi(gf::GF_OBJ_HANDLE* handle, bool use) {
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
    if (chr) {
        chr->m_useNavi = use;
    }
}

bool Utility::AI_StartMovePosition(gf::GF_OBJ_HANDLE* handle, const mm::Vec3& pos, float value) {
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
    if (!chr) {
        return false;
    }
    if (BattleGlobal::sys()->m_challengeAnySuccess && !chr->IsForward()) {
        return false;
    }
    BattleCharacter::AI_MOVE_PARAM param;
    param.m_value1 = value;
    param.m_type = 10;
    param.m_pos = &pos;
    if (!chr->IsProcAI(true)) {
        return false;
    }
    return chr->AI_Move(static_cast<BattleCharacter::ACTION_ID>(chr->m_state), false, &param);
}

bool Utility::AI_StartMoveTarget(gf::GF_OBJ_HANDLE* handle, int target, float value0, float value1) {
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
    if (!chr) {
        return false;
    }
    if (BattleGlobal::sys()->m_challengeAnySuccess && !chr->IsForward()) {
        return false;
    }
    BattleCharacter::AI_MOVE_PARAM param;
    param.m_value0 = value0;
    param.m_value1 = value1;
    param.m_target = AI_GetCharacterHandle(target);
    if (!chr->IsProcAI(true)) {
        return false;
    }
    return chr->AI_Move(static_cast<BattleCharacter::ACTION_ID>(chr->m_state), false, &param);
}

bool Utility::AI_StartMoveFront(gf::GF_OBJ_HANDLE* handle, int target, float value0, float value1) {
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
    if (!chr) {
        return false;
    }
    if (BattleGlobal::sys()->m_challengeAnySuccess && !chr->IsForward()) {
        return false;
    }
    BattleCharacter::AI_MOVE_PARAM param;
    param.m_value0 = value0;
    param.m_value1 = value1;
    param.m_type = 2;
    param.m_target = AI_GetCharacterHandle(target);
    if (!chr->IsProcAI(true)) {
        return false;
    }
    return chr->AI_Move(static_cast<BattleCharacter::ACTION_ID>(chr->m_state), false, &param);
}

bool Utility::AI_StartMoveSide(gf::GF_OBJ_HANDLE* handle, int target, float value0, float value1) {
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
    if (!chr) {
        return false;
    }
    if (BattleGlobal::sys()->m_challengeAnySuccess && !chr->IsForward()) {
        return false;
    }
    BattleCharacter::AI_MOVE_PARAM param;
    param.m_value0 = value0;
    param.m_value1 = value1;
    param.m_type = 3;
    param.m_target = AI_GetCharacterHandle(target);
    if (!chr->IsProcAI(true)) {
        return false;
    }
    return chr->AI_Move(static_cast<BattleCharacter::ACTION_ID>(chr->m_state), false, &param);
}

bool Utility::AI_StartMoveLeft(gf::GF_OBJ_HANDLE* handle, int target, float value0, float value1) {
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
    if (!chr) {
        return false;
    }
    if (BattleGlobal::sys()->m_challengeAnySuccess && !chr->IsForward()) {
        return false;
    }
    BattleCharacter::AI_MOVE_PARAM param;
    param.m_value0 = value0;
    param.m_value1 = value1;
    param.m_type = 4;
    param.m_target = AI_GetCharacterHandle(target);
    if (!chr->IsProcAI(true)) {
        return false;
    }
    return chr->AI_Move(static_cast<BattleCharacter::ACTION_ID>(chr->m_state), false, &param);
}

bool Utility::AI_StartMoveRight(gf::GF_OBJ_HANDLE* handle, int target, float value0, float value1) {
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
    if (!chr) {
        return false;
    }
    if (BattleGlobal::sys()->m_challengeAnySuccess && !chr->IsForward()) {
        return false;
    }
    BattleCharacter::AI_MOVE_PARAM param;
    param.m_value0 = value0;
    param.m_value1 = value1;
    param.m_type = 5;
    param.m_target = AI_GetCharacterHandle(target);
    if (!chr->IsProcAI(true)) {
        return false;
    }
    return chr->AI_Move(static_cast<BattleCharacter::ACTION_ID>(chr->m_state), false, &param);
}

bool Utility::AI_StartMoveBack(gf::GF_OBJ_HANDLE* handle, int target, float value0, float value1) {
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
    if (!chr) {
        return false;
    }
    if (BattleGlobal::sys()->m_challengeAnySuccess && !chr->IsForward()) {
        return false;
    }
    BattleCharacter::AI_MOVE_PARAM param;
    param.m_value0 = value0;
    param.m_value1 = value1;
    param.m_type = 6;
    param.m_target = AI_GetCharacterHandle(target);
    if (!chr->IsProcAI(true)) {
        return false;
    }
    return chr->AI_Move(static_cast<BattleCharacter::ACTION_ID>(chr->m_state), false, &param);
}
bool Utility::AI_StartMoveFriendBack(gf::GF_OBJ_HANDLE* handle, float value0, float value1) {
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
    if (!chr) {
        return false;
    }
    if (BattleGlobal::sys()->m_challengeAnySuccess && !chr->IsForward()) {
        return false;
    }
    mm::mtl::FixedVector<unsigned char, 90> list;
    if (GetCharacterList(list, handle, static_cast<CHECK_CHR_NUM_MODE>(1), 0x63) > 0) {
        mm::Vec3 self = chr->m_pos;
        float nearest = 3.40282347e+38f;
        gf::GF_OBJ_HANDLE* friendHandle = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
        CharacterManager* manager = CharacterManager::sys();
        for (unsigned char index : list) {
            BattleCharacter* other = manager->GetCharacterConst(index);
            mm::Vec3 pos;
            Misc::GetObjectTransform(other->m_handle, pos, Misc::TRANS_TYPE_POS);
            float length = Misc::CalcSquareLength(pos, self);
            if (length < nearest) {
                friendHandle = other->m_handle;
                nearest = length;
            }
        }
        if (friendHandle != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
            BattleCharacter::AI_MOVE_PARAM param;
            param.m_value0 = value0;
            param.m_value1 = value1;
            param.m_type = 6;
            param.m_target = friendHandle;
            if (chr->IsProcAI(true)) {
                return chr->AI_Move(static_cast<BattleCharacter::ACTION_ID>(chr->m_state), false, &param);
            }
        }
    }
    return false;
}

bool Utility::AI_StartMoveSatellite(gf::GF_OBJ_HANDLE* handle, bool flag, float value) {
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
    if (!chr) {
        return false;
    }
    if (BattleGlobal::sys()->m_challengeAnySuccess && !chr->IsForward()) {
        return false;
    }
    BattleCharacter::AI_MOVE_PARAM param;
    param.m_value0 = 0.0f;
    param.m_value1 = value * (1.0f / 30.0f);
    param.m_type = flag ? 8 : 9;
    if (!chr->IsProcAI(true)) {
        return false;
    }
    return chr->AI_Move(static_cast<BattleCharacter::ACTION_ID>(chr->m_state), false, &param);
}

bool Utility::AI_StartMoveBackward(gf::GF_OBJ_HANDLE* handle, float value0, float value1) {
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
    if (!chr) {
        return false;
    }
    if (BattleGlobal::sys()->m_challengeAnySuccess && !chr->IsForward()) {
        return false;
    }
    BattleCharacter::AI_MOVE_PARAM param;
    param.m_value0 = value0;
    param.m_value1 = value1;
    param.m_type = 7;
    if (!chr->IsProcAI(true)) {
        return false;
    }
    return chr->AI_Move(static_cast<BattleCharacter::ACTION_ID>(chr->m_state), false, &param);
}

bool Utility::AI_StartMovePosBackward(gf::GF_OBJ_HANDLE* handle, mm::Vec3& pos, float value) {
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
    if (!chr) {
        return false;
    }
    if (BattleGlobal::sys()->m_challengeAnySuccess && !chr->IsForward()) {
        return false;
    }
    mm::Vec3 dest;
    if (Misc::CalcDirectionXZ(chr->m_pos, pos, dest)) {
        dest = dest * 0.7f;
        dest += pos;
    } else {
        dest = pos;
    }
    BattleCharacter::AI_MOVE_PARAM param;
    param.m_value0 = 0.0f;
    param.m_value1 = value;
    param.m_type = 7;
    param.m_pos = &dest;
    if (!chr->IsProcAI(true)) {
        return false;
    }
    return chr->AI_Move(static_cast<BattleCharacter::ACTION_ID>(chr->m_state), false, &param);
}

bool Utility::AI_MoveStop(gf::GF_OBJ_HANDLE* handle, bool flag) {
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
    if (chr) {
        return chr->MoveStop(flag);
    }
    return false;
}

bool Utility::AI_IsDestruct(gf::GF_OBJ_HANDLE* handle) {
    return false;
}

bool Utility::AI_CheckState(gf::GF_OBJ_HANDLE* handle, CHECK_STATE state, int arg) {
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
    if (!chr) {
        return false;
    }
    switch (state) {
    case 0:
        return chr->IsBattle();
    case 1:
        return chr->m_state == 7;
    case 2:
        return arg > 0 ? chr->m_reactionID == arg : chr->m_reactionID != 0;
    case 3:
        return chr->IsDead(0);
    case 4:
        return BladeChangeManager::sys()->IsRegister(handle);
    case 5:
        return chr->m_state == 9;
    case 6:
        return chr->m_state == 12;
    case 7:
        return chr->IsRescue();
    case 8:
        return ChainAttackManager::sys()->IsProc(false);
    case 9:
        return chr->pad_DD4 >= 0;
    case 10:
        return chr->IsMove();
    case 11:
        return chr->pad_EF8 > 0x98;
    case 12: {
        const mm::Vec3& pos = chr->m_pos;
        const CharacterParameter* param = chr->GetCharacterParameterConst(true);
        return Misc::IsInWater(pos, param ? param->pad_30 * 1.5f : 3.0f);
    }
    case 13:
        return chr->pad_107C > 0.0f;
    case 14:
        return chr->IsProcAI(false);
    case 15:
        return chr->IsScout();
    case 16:
        return chr->IsElementalAwake();
    }
    return false;
}

int Utility::AI_GetAutoAttackState(gf::GF_OBJ_HANDLE* handle) {
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
    if (chr && chr->m_state == 6 && chr->m_isAutoAttack) {
        int state = chr->m_autoAttackStep + 1;
        return state < 0 ? 0 : (state > 3 ? 3 : state);
    }
    return 0;
}

int Utility::AI_GetTargetDirection(gf::GF_OBJ_HANDLE* target, gf::GF_OBJ_HANDLE* handle) {
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
    if (chr) {
        bool invalid;
        unsigned char position = chr->CheckAttackPosition(target, false, &invalid);
        if (invalid) {
            return 0;
        }
        return position < 4 ? position + 1 : 0;
    }
    return 0;
}

int Utility::AI_CheckCharacterNum(gf::GF_OBJ_HANDLE* handle, int direction, CHECK_CHR_NUM_MODE mode) {
    int num = 0;
    mm::mtl::FixedVector<unsigned char, 90> list;
    if (GetCharacterList(list, handle, mode, 0x63) > 0) {
        int position = direction >= 1 && direction <= 4 ? direction - 1 : -1;
        CharacterManager* manager = CharacterManager::sys();
        for (unsigned char index : list) {
            bool invalid;
            unsigned char pos = manager->GetCharacterConst(index)->CheckAttackPosition(handle, false, &invalid);
            num += !invalid && pos == position;
        }
    }
    return num;
}

int Utility::AI_CheckHpRateCharacterNum(gf::GF_OBJ_HANDLE* handle, int rate, CHECK_CHR_NUM_MODE mode) {
    int num = 0;
    mm::mtl::FixedVector<unsigned char, 90> list;
    if (GetCharacterList(list, handle, mode, 0x23) > 0) {
        float threshold = rate * 0.01f;
        CharacterManager* manager = CharacterManager::sys();
        for (unsigned char index : list) {
            const CharacterParameter* param = manager->GetCharacterConst(index)->GetCharacterParameterConst(true);
            if (param) {
                num += param->GetHPRate() <= threshold;
            }
        }
    }
    return num;
}

int Utility::AI_GetDeadCharacterNum(gf::GF_OBJ_HANDLE* handle, CHECK_CHR_NUM_MODE mode) {
    mm::mtl::FixedVector<unsigned char, 90> list;
    return GetCharacterList(list, handle, mode, 0x65);
}

int Utility::AI_GetDeadCharacterNumIncludeNoBattle(gf::GF_OBJ_HANDLE* handle, CHECK_CHR_NUM_MODE mode) {
    mm::mtl::FixedVector<unsigned char, 90> list;
    return GetCharacterList(list, handle, mode, 0x64);
}

void Utility::AI_AddKizuna(gf::GF_OBJ_HANDLE* handle, int value) {
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
    if (chr) {
        chr->AddKizuna(value);
    }
}

int Utility::AI_GetKizunaStage(gf::GF_OBJ_HANDLE* handle) {
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
    if (chr) {
        return chr->GetKizunaStage(nullptr);
    }
    return 0;
}

int Utility::AI_GetSpAttackLevel(gf::GF_OBJ_HANDLE* handle) {
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
    if (!chr) {
        return 0;
    }
    const GROUP_DATA* group = chr->GetGroupDataConst();
    if (!group || !group->m_isValid) {
        return 0;
    }
    int level = group->pad_115;
    if (level < 0) {
        return 0;
    }
    if (level == 15) {
        return 4;
    }
    return level + 1;
}

bool Utility::AI_IsEnableSpAttack(gf::GF_OBJ_HANDLE* handle, int level) {
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
    if (!chr) {
        return false;
    }
    if (BattleGlobal::sys()->m_challengeAnySuccess && !chr->IsForward()) {
        return false;
    }
    if (level != 0 && AI_GetSpAttackLevel(handle) != level) {
        return false;
    }
    if (!chr->IsProcAI(false)) {
        return false;
    }
    return chr->AI_SpAttack(static_cast<BattleCharacter::ACTION_ID>(chr->m_state), true, false);
}

bool Utility::AI_StartSpAttack(gf::GF_OBJ_HANDLE* handle) {
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
    if (!chr) {
        return false;
    }
    if (BattleGlobal::sys()->m_challengeAnySuccess && !chr->IsForward()) {
        return false;
    }
    if (!chr->IsProcAI(false)) {
        return false;
    }
    return chr->AI_SpAttack(static_cast<BattleCharacter::ACTION_ID>(chr->m_state), false, false);
}

bool Utility::AI_IsBattleOpening(gf::GF_OBJ_HANDLE* handle) {
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
    if (chr) {
        bool opening = chr->m_battleOpening;
        chr->m_battleOpening = false;
        return opening;
    }
    return false;
}

bool Utility::AI_IsInAttackRange(gf::GF_OBJ_HANDLE* handle) {
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
    if (chr) {
        return chr->IsInAttackRange(-1, nullptr);
    }
    return false;
}

bool Utility::AI_IsEnableArts(gf::GF_OBJ_HANDLE* handle, int slot, int target) {
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
    if (!chr) {
        return false;
    }
    return chr->IsEnableArts(-1, slot, 0, AI_GetCharacterHandle(target)) == 0;
}

bool Utility::AI_IsEnableArtsByID(gf::GF_OBJ_HANDLE* handle, int id, int target) {
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
    if (chr) {
        int slot = chr->GetArtsSlotIndex(id);
        if (slot >= 0) {
            return AI_IsEnableArts(handle, slot, target);
        }
    }
    return false;
}

bool Utility::AI_IsEnableTalentArts(gf::GF_OBJ_HANDLE* handle, int target) {
    if (!BattleGlobal::sys()->m_challengeAnySuccess) {
        return false;
    }
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
    if (!chr || !chr->IsForward()) {
        return false;
    }
    if (chr->pad_F09_3 || !chr->pad_F09_4) {
        return false;
    }
    return chr->IsEnableArts(0, 7, 0, AI_GetCharacterHandle(target)) == 0;
}

int Utility::AI_SearchVoiceCodeCharacter(int voiceCode) {
    CharacterManager* manager = CharacterManager::sys();
    for (int i = 0; i < 90; i++) {
        BattleCharacter* chr = manager->GetCharacterConst(i);
        if (chr && atoi(chr->m_voiceCode) == voiceCode) {
            return chr->GetAiChrID();
        }
    }
    return -1;
}

int Utility::AI_GetVoiceCode(gf::GF_OBJ_HANDLE* handle) {
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
    if (chr) {
        return atoi(chr->m_voiceCode);
    }
    return 0;
}

unsigned long Utility::AI_PlayVoice(gf::GF_OBJ_HANDLE* handle, int voice) {
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
    if (chr) {
        return TalkManager::sys()->PlayVoice(chr->m_voiceIndex, voice);
    }
    return 0;
}

int Utility::AI_GetPlayVoiceID(gf::GF_OBJ_HANDLE* handle) {
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
    if (chr) {
        return TalkManager::sys()->GetPlayVoiceID(chr->m_voiceIndex);
    }
    return 0;
}

void Utility::AI_SetBladeArtsRecastByLevel(gf::GF_OBJ_HANDLE* handle, int level, bool flag) {
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
    if (!chr) {
        return;
    }
    if (chr->IsDriver(false)) {
        CharacterParameter* param = chr->GetCharacterParameterConst(true);
        chr = CharacterManager::sys()->GetCharacterConst(param->m_driverHandle);
        if (!chr) {
            return;
        }
    }
    chr->SetSpAttackRecastByLevel(level, flag);
}

bool Utility::AI_IsBuff(gf::GF_OBJ_HANDLE* handle, int buff) {
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
    if (chr) {
        CharacterParameter* param = chr->GetCharacterParameter(true);
        if (param) {
            return param->IsBuff(buff);
        }
    }
    return false;
}

bool Utility::AI_IsProcSpAttack() {
    return SpAttackManager::sys()->m_procCount > 0;
}

int Utility::AI_GetBdatID(gf::GF_OBJ_HANDLE* handle) {
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
    if (chr) {
        return chr->m_bdatID;
    }
    return 0;
}

bool Utility::AI_IsPartyMember(unsigned int id) {
    mm::mtl::FixedVector<unsigned char, 90> list;
    GetCharacterList(list, gf::GfGameManager::getPartyLeaderDriver(), static_cast<CHECK_CHR_NUM_MODE>(1), 0);
    for (int index : list) {
        BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(index);
        if (chr->m_bdatID == id) {
            return true;
        }
    }
    return false;
}

bool Utility::AI_GetCharacterGimmickPoint(gf::GF_OBJ_HANDLE* handle, mm::Vec3& pos) {
    return gf::GfGameUtil::getGmkTargetPointPos(pos, handle);
}

bool Utility::AI_GetGimmickPoint(mm::Vec3& pos, unsigned int id) {
    return gf::GfGameUtil::getGmkTargetPointPos(pos, id);
}

void Utility::AI_SetScout(gf::GF_OBJ_HANDLE* handle, bool flag) {
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
    if (chr) {
        chr->SetScout(flag);
    }
}

void Utility::AI_SetSuperArmor(gf::GF_OBJ_HANDLE* handle, float time) {
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
    if (chr) {
        chr->SetSuperArmorTime(time);
    }
}

bool Utility::AI_IsEnableButtonChallenge() {
    if (!BattleGlobal::sys()->pad_bit1 || !BattleGlobal::sys()->IsEnableBattle()) {
        return false;
    }
    if (ChainAttackManager::sys()->IsProc(false)) {
        return false;
    }
    if (BladeArtsManager::sys()->m_procNum > 0 || SpAttackManager::sys()->m_procCount > 0) {
        return false;
    }
    return !BattleGlobal::sys()->m_buttonChallenge.IsProc();
}

bool Utility::AI_RegisterButtonChallenge(int id, bool sequence) {
    if (!AI_IsEnableButtonChallenge()) {
        return false;
    }
    ButtonChallenge::BUTTON_CHALLENGE_PARAM param;
    param.m_menuType = sequence ? 0xF9 : 0xF8;
    param.m_menuId = id;
    param.m_kind = 2;
    param.m_character = CharacterManager::sys()->m_controlIndex;
    BattleGlobal::sys()->m_buttonChallenge.Start(param);
    return true;
}

int Utility::AI_GetButtonChallengeResult() {
    ButtonChallenge* challenge = &BattleGlobal::sys()->m_buttonChallenge;
    if (challenge->IsProc() && challenge->m_param.m_kind == 2) {
        return 0;
    }
    return challenge->IsEnemyChallengeSuccess() ? 1 : 2;
}

int Utility::AI_EnemyKillNum() {
    return BattleGlobal::sys()->m_enemyKillNum;
}

bool Utility::AI_IsKillChild() {
    return BattleGlobal::sys()->m_killChild;
}

bool Utility::AI_IsUseSirenSp() {
    return BattleGlobal::sys()->pad_bit55;
}

bool Utility::AI_IsBenkeiWeather() {
    return DataManager::sys()->IsSpecialEffects(2);
}

float Utility::AI_GetPartyGaugeNum() {
    int gauge = DataManager::get()->GetPartyGauge();
    return gauge > 299 ? 3.0f : gauge * 0.0033333334f;
}

float Utility::AI_GetEnemySirenSpGaugeRate() {
    return SirenBattleManager::get()->m_sides[1].m_gauge;
}

void Utility::AI_AddEnemySirenSpGaugeRate(float ratio) {
    SirenBattleManager::get()->AddSirenSpGaugeRate(ratio, false);
}

int Utility::AI_GetSirenBuffLevel(bool white) {
    SirenBattleManager* siren = SirenBattleManager::get();
    return siren->m_sides[!white].m_level;
}

int Utility::AI_GetChallengeID() {
    if (ChallengeBattleManager::get()->IsProc()) {
        return 0;
    }
    return ChallengeBattleManager::get()->pad_2a;
}

}  // namespace btl
