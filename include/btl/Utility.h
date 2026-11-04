#ifndef BTL_UTILITY_H
#define BTL_UTILITY_H

#include "classes/btl/DataManager.h"

namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class MsgObjectNotifyDead; }
namespace mm { namespace mtl { template <typename, unsigned long> class FixedVector; }}

namespace mm { class Vec3; }

namespace btl { namespace Utility {
void GetArtsData(ARTS_DATA::DATA_TYPE type, int id, ARTS_DATA& data);
// the id of the arts' enhance at index (1-based; ARTS_DATA::m_enhances[index - 1])
unsigned short GetArtsEnhance(const ARTS_DATA& data, int index);
int GetElementalEffectID();
int GetUniteComboID(int, int);
float GetDyingHpRate();
bool AI_IsProcSpAttack();
bool AI_IsBenkeiWeather();
gf::GF_OBJ_HANDLE* GetLeader();
gf::GF_OBJ_HANDLE* GetControlCharacterHandle();
bool IsSatisfyCondition(int condition);
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
bool IsEnableEventStart();
// false while the party leader fights outside state 3, while TalkManager forbids it, or while BattleGlobal::m_challengeAnySuccess
// is set and FormationChangeManager has requests queued
bool IsEnableFieldBladeChange();
// 2.0.0's symbols name it. What it does: sets bit 7 of the 32-bit word at BattleGlobal+0x83CA (rewriting the halfword
// at 0x83CE and the byte at 0x83D0 unchanged); its only caller is GfPlayComWaitBattleEnd::start, when the event after
// the battle is of type 1..3 and GfGameScene::isNeedResetBladeForBattleEndForBattleEnd holds.
void NotifyNeedPutAwayWeapon();
// fills the list with the indices of the characters the handle's character sees (EnemyParameter::CheckChangeAttr
// passes mode 0 and 0x23, AngryInfection mode 1 and 0x62) and returns how many
int GetCharacterList(mm::mtl::FixedVector<unsigned char, 90>& list, gf::GF_OBJ_HANDLE* handle,
                     CHECK_CHR_NUM_MODE mode, unsigned int flags);
bool AI_IsAngry(gf::GF_OBJ_HANDLE* handle);
bool AI_SetAngry(gf::GF_OBJ_HANDLE* handle, float time);
bool AI_TurnTarget(gf::GF_OBJ_HANDLE* handle);
bool AI_StartActionEscape(gf::GF_OBJ_HANDLE* handle);
bool AI_MoveStop(gf::GF_OBJ_HANDLE* handle, bool);
void AI_AddKizuna(gf::GF_OBJ_HANDLE* handle, int value);
int AI_GetKizunaStage(gf::GF_OBJ_HANDLE* handle);
bool AI_IsInAttackRange(gf::GF_OBJ_HANDLE* handle);
// a 64-bit value from the talk manager's entry for the voice (its type is not known), 0 when none plays (the
// aiData script method playVoice tests it)
unsigned long AI_PlayVoice(gf::GF_OBJ_HANDLE* handle, int voice);
int AI_GetPlayVoiceID(gf::GF_OBJ_HANDLE* handle);
void AI_SetScout(gf::GF_OBJ_HANDLE* handle, bool);
void AI_SetSuperArmor(gf::GF_OBJ_HANDLE* handle, float time);
// StateFieldOnGround::update asks it for the PC's handle before starting a field battle (by its symbol)
bool IsBattleStart(gf::GF_OBJ_HANDLE* handle);
// which SCOM_ENBOOK_* command RegisterEnemyBook creates: 0 IN_BATTLE, 1 BOSS_TIME, 2 DEFEAT_ENEMY, 3 DEAD_PLAYER
enum ENBOOK_TYPE : int;
void RegisterEnemyBook(ENBOOK_TYPE type, gf::GF_OBJ_HANDLE* handle, int value);
int AI_GetDeadCharacterNum(gf::GF_OBJ_HANDLE* handle, CHECK_CHR_NUM_MODE mode);
// 2.0.0's symbols name it. What it does: as AI_GetDeadCharacterNum with GetCharacterList flags 0x64 instead of 0x65
// (its only caller is CheckTalentArtsCondition).
int AI_GetDeadCharacterNumIncludeNoBattle(gf::GF_OBJ_HANDLE* handle, CHECK_CHR_NUM_MODE mode);
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
// 2.0.0's symbols name them. What it does: true when BattleGlobal::IsPause(-1) or BattleGlobal's float at +0xA50 is <=
// 0 (btl_ai.isPause).
bool IsPause();
// 2.0.0's symbols name StartChallengeBattleCallback, EndChallengeBattleCallback, RetryChallengeBattleCallback,
// ChallengeBattleStartTelopCallback, IsBattleAutoHeal; the fn_ names are placeholders. What they do: call
// ChallengeBattleManager (the challenge battle singleton) Start (enter calls it), End (fn_710028FFF4), Retry
// (execAfterBattle), NotifyStartTelop (execBattleStart), AddEtherCube(value) (GfFobjDropitem::applyGetItem) and
// IsEnableAutoHeal (GfGameScene::updateAutoHeal).
void StartChallengeBattleCallback();
void EndChallengeBattleCallback();
void RetryChallengeBattleCallback();
void ChallengeBattleStartTelopCallback();
void PickupEtherCube(int value, gf::GF_OBJ_HANDLE*);
bool IsBattleAutoHeal();
// What it does: BattleCharacter::NotifyDead(msg) on the handle's character when it has one
// (GfComBehaviorPc::procMsgObjectNotifyDead).
void NotifyDead(gf::GF_OBJ_HANDLE* handle, const gf::MsgObjectNotifyDead& msg);
// What it does: ChallengeBattleManager::IsEnableEnemyBattle while BattleGlobal::IsEnableBattle holds, else false
// (BattleCharacter::UpdateHateRingData, GfComBehaviorEnemy::canChangeBattle).
bool IsEnableEnemyBattle();
// What it does: BattleCharacter::IsAutoHeal on the handle's character, true without one
// (GfGameScene::updateAutoHeal).
bool IsCharacterAutoHeal(gf::GF_OBJ_HANDLE* handle);
// What they do: GetIraGroupDriverID maps ids 17-23 to a driver (17, 18, 19, 17, 17, 18, 18; else 19), GetIraBladeSlot ids
// 20-25 to a slot (0, 1, 0, 1, 0, 1; else -1); GetIraDummyBladeID passes both to GfDataBlade::fn_7100237B70.
// What it does: when the second handle is a battle character, 0 for a non-player, 2 for one of the controlled group,
// 1 for another; else 2 when the first handle is an enemy object (GfObjUtil::getObjType 5) and 0 otherwise, the
// other way round when the flag is set (the parameter names are not the original's).
int GetDamageAttackerType(gf::GF_OBJ_HANDLE* object, gf::GF_OBJ_HANDLE* attacker, bool);
// 2.0.0's symbols name them. EntangleEnemy:
// GfSmnEnemyManager::execAbsSummon({handle, radius, group, 0}) (BattleCharacter::JoinProc, BattleEndInitialize). IsForward:
// whether the handle is the driver of party group 0, 1 or 2 (none for -1; CharacterParameter::PreUpdate,
// PlayerParameter::Initialize).
void EntangleEnemy(gf::GF_OBJ_HANDLE* handle, float radius, int group);
bool IsForward(gf::GF_OBJ_HANDLE* handle);
int GetIraGroupDriverID(unsigned int blade);
int GetIraBladeSlot(unsigned int blade);
// What it does: true unless ChallengeBattleManager::IsEnableOperate (true without a challenge battle) holds and IsEnableOperate on
// the siren battle singleton (lbl_7100B939D0) returns true; PadField's action and axis handlers ignore the pad
// while it is true (3.0.1's PadField::decideAction etc. call it where 1.0.0's had nothing).
bool IsBanOperateForField();
// 2.0.0's symbols name it. What it does: false while BattleGlobal::IsPause(-1), BattleGlobal's ButtonChallenge runs,
// ChainAttackManager::IsProc(true) or BattleGlobal::IsFutureView holds, else true (BattleGlobal::UpdateProc,
// BattleCharacter::DropItem).
bool IsEnablePreciousDrop();
// What it does: sets btl::DataManager's byte at +0x15D1A to 1 (the btl_ai entry after setKizunaStage).
void FullCoolTime();
// What it does: stores its argument at BattleGlobal +0x5DD8 (the last btl_ai entry; the script passes an int).
void SetBattleEndEnemyCall(float value);
// What it does: KIZUNA_GAUGE_DATA::SetKizunaStage(stage) on every blade of the three party groups, or only the
// engaged one when the second argument is set (btl_ai.setKizunaStage: stage defaults to 6, flag to false).
void SetPlayerKizunaStage(int stage, bool);
// What it does: the bool btl_ai.isUseSirenSp returns.
bool AI_IsUseSirenSp();
// What it does: the fixed value btl_ai.getPartyGaugeNum returns.
float AI_GetPartyGaugeNum();
// What it does: the fixed value btl_ai.getEnemySirenGaugeRatio returns (addEnemySirenGaugeRatio returns it too).
float AI_GetEnemySirenSpGaugeRate();
// What it does: what btl_ai.addEnemySirenGaugeRatio does with its fixed argument.
void AI_AddEnemySirenSpGaugeRate(float ratio);
// What it does: btl_ai.getWhiteSirenLevel passes 1, getBlackSirenLevel 0; returns the level.
int AI_GetSirenBuffLevel(bool white);
// What it does: the int btl_ai.getChallengeID returns.
int AI_GetChallengeID();
// The ones below are what the aiData script methods (application/BF2/unit_7100652854) call; the return types are what those test.
void AI_AddBladeArtsRecast(gf::GF_OBJ_HANDLE* handle, float time, bool);
int AI_GetLinkCharacterID(gf::GF_OBJ_HANDLE* handle);
float AI_GetVertDiff(gf::GF_OBJ_HANDLE* handle, gf::GF_OBJ_HANDLE* target);
int AI_GetEatTargetCharacterID(gf::GF_OBJ_HANDLE* handle, float);
int AI_GetFightComboID(gf::GF_OBJ_HANDLE* handle);
int AI_GetElementalComboID(gf::GF_OBJ_HANDLE* handle);
int AI_GetCharacterAIID(gf::GF_OBJ_HANDLE* handle);
int AI_SearchVoiceCodeCharacter(int voiceCode);
int AI_GetBackAttackerCharacterID(gf::GF_OBJ_HANDLE* handle);
// the second handle's character answers where the first stands (CheckAttackPosition)
int AI_GetTargetDirection(gf::GF_OBJ_HANDLE* target, gf::GF_OBJ_HANDLE* handle);
int AI_CheckCharacterNum(gf::GF_OBJ_HANDLE* handle, int, CHECK_CHR_NUM_MODE mode);
int AI_CheckHpRateCharacterNum(gf::GF_OBJ_HANDLE* handle, int, CHECK_CHR_NUM_MODE mode);
int AI_GetSpAttackLevel(gf::GF_OBJ_HANDLE* handle);
int AI_GetReactionID(gf::GF_OBJ_HANDLE* handle);
int AI_GetBdatID(gf::GF_OBJ_HANDLE* handle);
int AI_GetAutoAttackState(gf::GF_OBJ_HANDLE* handle);
bool AI_StartActionRescue(gf::GF_OBJ_HANDLE* handle, int);
bool AI_StartActionArts(gf::GF_OBJ_HANDLE* handle, int, int);
bool AI_StartActionArtsByID(gf::GF_OBJ_HANDLE* handle, int id, int);
bool AI_StartActionAttack(gf::GF_OBJ_HANDLE* handle);
bool AI_StartActionBladeChange(gf::GF_OBJ_HANDLE* handle, int);
bool AI_StartSpAttack(gf::GF_OBJ_HANDLE* handle);
bool AI_StartMoveSide(gf::GF_OBJ_HANDLE* handle, int target, float, float);
bool AI_StartMoveBack(gf::GF_OBJ_HANDLE* handle, int target, float, float);
bool AI_StartMoveFront(gf::GF_OBJ_HANDLE* handle, int target, float, float);
bool AI_StartMoveLeft(gf::GF_OBJ_HANDLE* handle, int target, float, float);
bool AI_StartMoveRight(gf::GF_OBJ_HANDLE* handle, int target, float, float);
bool AI_StartMoveTarget(gf::GF_OBJ_HANDLE* handle, int target, float, float);
bool AI_StartMoveFriendBack(gf::GF_OBJ_HANDLE* handle, float, float);
bool AI_StartMoveBackward(gf::GF_OBJ_HANDLE* handle, float, float);
bool AI_StartMoveSatellite(gf::GF_OBJ_HANDLE* handle, bool, float);
bool AI_StartMovePosition(gf::GF_OBJ_HANDLE* handle, const mm::Vec3& pos, float);
bool AI_StartMovePosBackward(gf::GF_OBJ_HANDLE* handle, mm::Vec3& pos, float);
bool AI_TurnDirection(gf::GF_OBJ_HANDLE* handle, const mm::Vec3& dir);
void AI_SetUseNavi(gf::GF_OBJ_HANDLE* handle, bool);
bool AI_IsBattleOpening(gf::GF_OBJ_HANDLE* handle);
bool AI_IsEnableArts(gf::GF_OBJ_HANDLE* handle, int, int);
bool AI_IsEnableArtsByID(gf::GF_OBJ_HANDLE* handle, int id, int);
bool AI_IsEnableSpAttack(gf::GF_OBJ_HANDLE* handle, int);
// 2.0.0's symbols name them. AI_GetResistantAttrNum: aiData's getElemBall returns its int.
int AI_GetResistantAttrNum(gf::GF_OBJ_HANDLE* handle);
// AI_StartActionTalentArts: aiData's actionTalentArts starts an action with it and returns its bool.
bool AI_StartActionTalentArts(gf::GF_OBJ_HANDLE* handle);
// AI_IsEnableTalentArts: aiData's isTalentArts passes it -1 and returns its bool.
bool AI_IsEnableTalentArts(gf::GF_OBJ_HANDLE* handle, int);
// AI_GetBladeBdatID: aiData's getTargetBladeId calls it on the target (getTargetDriverId calls AI_GetBdatID the same
// way) and returns its int, -1 for 0.
int AI_GetBladeBdatID(gf::GF_OBJ_HANDLE* handle);
// GROUP_BLADE_DATA::Initialize and InitializeCoolTime pass the blade's id
float GetBladeCoolTime(int blade);
// 2.0.0's symbols name it. A free function of the Utility namespace: it
// sits in Utility's unit among its functions (no this). What it does: maps an id through the tables at
// 0x71009B5BD0 (ids 17-23) and 0x71009B5BF0 (ids 20-25) to a blade id; GROUP_BLADE_DATA::GetTrustRank passes its
// blade's id when BattleGlobal::pad_bit35 is set and asks the trust rank of the result.
unsigned int GetIraDummyBladeID(unsigned int blade);
}}  // namespace btl::Utility

#endif
