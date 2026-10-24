#ifndef BTL_UTILITY_H
#define BTL_UTILITY_H

#include "classes/btl/DataManager.h"

namespace gf { class GF_OBJ_HANDLE; }
namespace mm { namespace mtl { template <typename, unsigned long> class FixedVector; }}

namespace mm { class Vec3; }

namespace btl { namespace Utility {
void GetArtsData(ARTS_DATA::DATA_TYPE type, int id, ARTS_DATA& data);
unsigned char GetElementalEffectID();
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
}}  // namespace btl::Utility

#endif
