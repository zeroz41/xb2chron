#ifndef BTL_UTILITY_H
#define BTL_UTILITY_H

#include "classes/btl/DataManager.h"

namespace gf { class GF_OBJ_HANDLE; }
namespace mm { namespace mtl { template <typename, unsigned long> class FixedVector; }}

namespace mm { class Vec3; }

namespace btl { namespace Utility {
void GetArtsData(ARTS_DATA::DATA_TYPE type, int id, ARTS_DATA& data);
int GetElementalEffectID();
int GetUniteComboID(int, int);
float GetDyingHpRate();
bool AI_IsProcSpAttack();
bool AI_IsBenkeiWeather();
gf::GF_OBJ_HANDLE* GetLeader();
gf::GF_OBJ_HANDLE* GetControlCharacterHandle();
bool IsSatisfyConditionFld(int condition);
unsigned int GetTrustRank(int blade);
int GetWeaponSeType(int weaponType);
int GetAttrSeType(int attr);
int GetAntiAttribute(unsigned int attr);
bool IsThirdCharacter(gf::GF_OBJ_HANDLE* handle);
bool IsBladeArtsBuff(int buff);
bool AI_GetObjectPosition(gf::GF_OBJ_HANDLE* handle, mm::Vec3& pos);
bool AI_IsDestruct(gf::GF_OBJ_HANDLE* handle);
bool AI_GetCharacterGimmickPoint(gf::GF_OBJ_HANDLE* handle, mm::Vec3& pos);
bool AI_GetGimmickPoint(mm::Vec3& pos, unsigned int id);
enum CHECK_CHR_NUM_MODE : int;
// the states AI_CheckState tests (ai::AiData::isValid asks 1, 3, 4, 5, 7, 8 and 9; update asks 1)
enum CHECK_STATE : int {};
bool AI_CheckState(gf::GF_OBJ_HANDLE* handle, CHECK_STATE state, int arg);
// the character id the handle's AI targets (ai::AiData::getHandleTarget turns it into a handle)
int AI_GetTargetCharacterID(gf::GF_OBJ_HANDLE* handle);
gf::GF_OBJ_HANDLE* AI_GetCharacterHandle(int id);
bool AI_IsValidID(int id);
int AI_GetRescueTargetCharacterID(gf::GF_OBJ_HANDLE* handle);
int AI_GetStamp(gf::GF_OBJ_HANDLE* handle);
bool AI_IsFly(gf::GF_OBJ_HANDLE* handle);
int AI_GetEnemyNum();
int AI_GetPlayerNum();
bool IsEnableDeadSequence();
// fills the list with the indices of the characters the handle's character sees (EnemyParameter::CheckChangeAttr
// passes mode 0 and 0x23, AngryInfection mode 1 and 0x62) and returns how many
int GetCharacterList(mm::mtl::FixedVector<unsigned char, 90>& list, gf::GF_OBJ_HANDLE* handle,
                     CHECK_CHR_NUM_MODE mode, unsigned int flags);
bool AI_IsAngry(gf::GF_OBJ_HANDLE* handle);
void AI_SetAngry(gf::GF_OBJ_HANDLE* handle, float time);
bool AI_TurnTarget(gf::GF_OBJ_HANDLE* handle);
void AI_StartActionEscape(gf::GF_OBJ_HANDLE* handle);
void AI_MoveStop(gf::GF_OBJ_HANDLE* handle, bool);
void AI_AddKizuna(gf::GF_OBJ_HANDLE* handle, int value);
int AI_GetKizunaStage(gf::GF_OBJ_HANDLE* handle);
bool AI_IsInAttackRange(gf::GF_OBJ_HANDLE* handle);
void AI_PlayVoice(gf::GF_OBJ_HANDLE* handle, int voice);
int AI_GetPlayVoiceID(gf::GF_OBJ_HANDLE* handle);
void AI_SetScout(gf::GF_OBJ_HANDLE* handle, bool);
void AI_SetSuperArmor(gf::GF_OBJ_HANDLE* handle, float time);
// StateFieldOnGround::update asks it for the PC's handle before starting a field battle (by its symbol)
bool IsBattleStart(gf::GF_OBJ_HANDLE* handle);
// read by the btl_ai script plugin (ScriptCamMotion's unit)
int AI_GetTargetedCharacterID(gf::GF_OBJ_HANDLE* handle);
int AI_GetAimCharacterNum(gf::GF_OBJ_HANDLE* handle);
int AI_GetStampCharacterID(int stamp);
float AI_GetHpPercent(gf::GF_OBJ_HANDLE* handle);
int AI_GetLevel(gf::GF_OBJ_HANDLE* handle);
int AI_GetAttribute(gf::GF_OBJ_HANDLE* handle);
int AI_GetVoiceCode(gf::GF_OBJ_HANDLE* handle);
bool AI_IsBuff(gf::GF_OBJ_HANDLE* handle, int buff);
bool AI_RegisterButtonChallenge(int id, bool);
int AI_GetButtonChallengeResult();
bool AI_IsEnableButtonChallenge();
void AI_SetBladeArtsRecastByLevel(gf::GF_OBJ_HANDLE* handle, int level, bool);
void AI_SetResistantAttr(int attr);
// 1.0.0's names for these (its btl_ai plugin calls them where 3.0.1's does)
int AI_GetArtsEnemyNum();
int AI_GetArtsPlayerNum();
int AI_EnemyKillNum();
bool AI_IsPartyMember(unsigned int id);
bool AI_IsKillChild();
// Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them. In btl::Utility because they sit among its
// functions (0x710000FB7C..0x710001535C) and only the btl_ai script plugin calls them.
// What it does: true when BattleGlobal::IsPause(-1) or BattleGlobal's float at +0xA50 is <= 0 (btl_ai.isPause).
bool fn_710000FB7C();
// What it does: sets btl::DataManager's byte at +0x15D1A to 1 (the btl_ai entry after setKizunaStage).
void fn_7100010D84();
// What it does: stores its argument at BattleGlobal +0x5DD8 (the last btl_ai entry; the script passes an int).
void fn_7100010DA4(float value);
// What it does: KIZUNA_GAUGE_DATA::SetKizunaStage(stage) on every blade of the three party groups, or only the
// engaged one when the second argument is set (btl_ai.setKizunaStage: stage defaults to 6, flag to false).
void fn_7100010DBC(int stage, bool);
// What it does: the bool btl_ai.isUseSirenSp returns.
bool fn_71000151EC();
// What it does: the fixed value btl_ai.getPartyGaugeNum returns.
float fn_71000152D0();
// What it does: the fixed value btl_ai.getEnemySirenGaugeRatio returns (addEnemySirenGaugeRatio returns it too).
float fn_710001530C();
// What it does: what btl_ai.addEnemySirenGaugeRatio does with its fixed argument.
void fn_7100015320(float ratio);
// What it does: btl_ai.getWhiteSirenLevel passes 1, getBlackSirenLevel 0; returns the level.
int fn_7100015334(int white);
// What it does: the int btl_ai.getChallengeID returns.
int fn_710001535C();
}}  // namespace btl::Utility

#endif
