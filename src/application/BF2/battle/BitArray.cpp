#include "btl/Utility.h"
#include "btl/Misc.h"
#include "classes/btl/BattleCharacter.h"
#include "classes/btl/BattleGlobal.h"
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

namespace btl {

bool Utility::fn_710000FB7C() {
    BattleGlobal* global = BattleGlobal::sys();
    if (global->IsPause(-1)) {
        return true;
    }
    return global->pad_a50 <= 0.0f;
}

gf::GF_OBJ_HANDLE* Utility::GetLeader() {
    return gf::GfGameManager::getPartyLeaderDriver();
}

gf::GF_OBJ_HANDLE* Utility::GetControlCharacterHandle() {
    ChainAttackManager* chain = ChainAttackManager::sys();
    if (chain->IsProc(false)) {
        int group = ChainAttackManager::sys()->GetGroupIndex();
        if (group >= 0) {
            return gf::GfGameParty::getHandleDriver(group, 0);
        }
    }
    return gf::GfGameManager::getPartyLeaderDriver();
}

bool Utility::IsSatisfyConditionFld(int condition) {
    return gf::GfGameCond::isGameCond(condition);
}

void Utility::fn_71000100F0() {
    BattleGlobal::sys()->pad_bit7 = true;
}

void Utility::GetArtsData(ARTS_DATA::DATA_TYPE type, int id, ARTS_DATA& data) {
    DataManager::sys()->GetArtsData(type, id, data);
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

int Utility::GetElementalEffectID() {
    return DataManager::sys()->m_elementalEffectID;
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

float Utility::GetDyingHpRate() {
    return BtlSystemBalanceAccess::sys()->m_dyingHpRate;
}

unsigned int Utility::GetTrustRank(int blade) {
    return gf::GfDataBlade::getTrustRank(blade);
}

void Utility::fn_7100010D84() {
    DataManager::sys()->pad_15D1A = 1;
}

void Utility::fn_7100010DA4(float value) {
    BattleGlobal::sys()->pad_5dd8 = value;
}

void Utility::fn_7100010DBC(int stage, bool engagedOnly) {
    DataManager::sys()->fn_71000968B8(stage, engagedOnly);
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
        if (chr && !chr->IsBlade() && !chr->IsDead(0)) {
            num += chr->IsBattle();
        }
    }
    return num;
}

int Utility::AI_GetPlayerNum() {
    int num = 0;
    for (int i = 0; i < 20; i++) {
        BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(i);
        if (chr && !chr->IsBlade() && !chr->IsDead(0)) {
            num += chr->IsBattle();
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

bool Utility::AI_StartActionEscape(gf::GF_OBJ_HANDLE* handle) {
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
    if (chr) {
        return chr->StartBackHome();
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

bool Utility::AI_TurnTarget(gf::GF_OBJ_HANDLE* handle) {
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
    if (chr && chr->IsEnableTurnAI()) {
        chr->TurnTarget(false, false, true);
        return true;
    }
    return false;
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

int Utility::AI_GetDeadCharacterNum(gf::GF_OBJ_HANDLE* handle, CHECK_CHR_NUM_MODE mode) {
    mm::mtl::FixedVector<unsigned char, 90> list;
    return GetCharacterList(list, handle, mode, 0x65);
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

bool Utility::AI_IsInAttackRange(gf::GF_OBJ_HANDLE* handle) {
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
    if (chr) {
        return chr->IsInAttackRange(-1, nullptr);
    }
    return false;
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

int Utility::AI_EnemyKillNum() {
    return BattleGlobal::sys()->m_enemyKillNum;
}

bool Utility::AI_IsKillChild() {
    return BattleGlobal::sys()->m_killChild;
}

bool Utility::fn_71000151EC() {
    return BattleGlobal::sys()->pad_bit55;
}

bool Utility::AI_IsBenkeiWeather() {
    return DataManager::sys()->IsSpecialEffects(2);
}

}  // namespace btl
