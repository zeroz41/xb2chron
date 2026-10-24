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

namespace btl {

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

unsigned char Utility::GetElementalEffectID() {
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

bool Utility::IsEnableDeadSequence() {
    return !TalkManager::sys()->IsPlayingEnemyWinVoice();
}

bool Utility::IsThirdCharacter(gf::GF_OBJ_HANDLE* handle) {
    return gf::GfObjUtil::isTrinityBlade(handle);
}

bool Utility::IsBladeArtsBuff(int buff) {
    return buff >= 1 && buff <= 9;
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

bool Utility::AI_IsFly(gf::GF_OBJ_HANDLE* handle) {
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
    if (chr) {
        return chr->m_isFly;
    }
    return false;
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

int Utility::AI_GetStamp(gf::GF_OBJ_HANDLE* handle) {
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
    if (chr && !chr->IsDead(0)) {
        return chr->m_stamp;
    }
    return 0;
}

void Utility::AI_StartActionEscape(gf::GF_OBJ_HANDLE* handle) {
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
    if (chr) {
        chr->StartBackHome();
    }
}

bool Utility::AI_IsAngry(gf::GF_OBJ_HANDLE* handle) {
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
    if (chr) {
        return chr->IsAngry();
    }
    return false;
}

void Utility::AI_SetAngry(gf::GF_OBJ_HANDLE* handle, float time) {
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
    if (chr) {
        chr->SetAngry(true, time);
    }
}

bool Utility::AI_TurnTarget(gf::GF_OBJ_HANDLE* handle) {
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
    if (chr && chr->IsEnableTurnAI()) {
        chr->TurnTarget(false, false, true);
        return true;
    }
    return false;
}

void Utility::AI_MoveStop(gf::GF_OBJ_HANDLE* handle, bool flag) {
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
    if (chr) {
        chr->MoveStop(flag);
    }
}

bool Utility::AI_IsDestruct(gf::GF_OBJ_HANDLE* handle) {
    return false;
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

bool Utility::AI_IsProcSpAttack() {
    return SpAttackManager::sys()->m_procCount > 0;
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

bool Utility::AI_IsBenkeiWeather() {
    return DataManager::sys()->IsSpecialEffects(2);
}

}  // namespace btl
