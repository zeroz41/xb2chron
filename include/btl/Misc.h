#ifndef BTL_MISC_H
#define BTL_MISC_H

#include "mm/Quat.h"
#include "mm/Vec3.h"

namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GfObj; }

namespace btl {

// the battle code's vector helpers (1.0.0's btl::Misc; 3.0.1 keeps the ones below in battle/Misc.cpp)
class BattleCharacter;
namespace Misc {
// whether chr is within range of pos (EnemyParameter::AngryInfection passes its character's position, the
// candidate, the candidate's radius plus its range, and false)
// the trust stage of a trust value
int GetKizunaStage(int kizuna, float* ratio);

bool CheckInRange(const mm::Vec3& pos, BattleCharacter* chr, float range, bool flag);
// the same for the object handle names (BattleCharacter::CheckWeaponDistance passes its target and false)
bool CheckInRange(const mm::Vec3& pos, gf::GF_OBJ_HANDLE* handle, float range, bool flag);

// the party the object belongs to, -1 for none (PlayerParameter::Update keeps its m_groupIndex then)
int GetPartyID(gf::GF_OBJ_HANDLE* handle);

// the alpha rate a volume fade gives the object (BattleCharacter::RegisterAlphaAnimation starts from it)
float GetVolumeFadeAlphaRate(gf::GF_OBJ_HANDLE* handle);

// which way GetCrossDirection turns: 0 one side, any other the opposite (the names are not the original's)
enum CROSS_MODE {
    CROSS_MODE_0 = 0,
};

// v to length 1: a zero one becomes unitZ, a tiny one is scaled up first, one still too short becomes zero
void Normalize(mm::Vec3& v);
// dir turned toward target by up to angle (radians) about their common normal; one within angle (and not force)
// becomes target. The angle between them, or angle when turned
float TurnDirectionAngle(mm::Vec3& dir, const mm::Vec3& target, float angle, bool force);
// the direction from from to to, false (and zero) when they are within 1e-6 of each other
bool CalcDirection(const mm::Vec3& from, const mm::Vec3& to, mm::Vec3& out);
// v turned a quarter about the Y axis in the XZ plane
void GetCrossDirection(const mm::Vec3& v, mm::Vec3& out, CROSS_MODE mode);
// the direction a rotation turns unitZ to
void GetPostureDirection(const mm::Quat& q, mm::Vec3& out);
// the angle between two directions; signed, negative when b lies the other way about the Y axis
float CalcAngle(const mm::Vec3& a, const mm::Vec3& b, bool isSigned);
// which transform GetObjectTransform reads (0: position; the names are not the original's)
enum TRANS_TYPE : int {
    TRANS_TYPE_POS = 0,
};
bool GetObjectTransform(gf::GF_OBJ_HANDLE* handle, mm::Vec3& out, TRANS_TYPE type);
// the angle of v about the Y axis from unitZ
float CalcRotY(const mm::Vec3& v);

// the helpers 3.0.1 keeps after battle/Misc.cpp's (ShakeCameraManager's unit)
// v to length 1 in the XZ plane (y 0); false (and unitZ) when it is within 1e-6 of zero there
bool NormalizeXZ(mm::Vec3& v);
float CalcLength(const mm::Vec3& a, const mm::Vec3& b);
float CalcSquareLength(const mm::Vec3& a, const mm::Vec3& b);
float CalcLengthXZ(const mm::Vec3& a, const mm::Vec3& b);
float CalcSquareLengthXZ(const mm::Vec3& a, const mm::Vec3& b);
float CalcLengthXZ(const mm::Vec3& v);
// the XZ direction from from to to, false (and unitZ) when they are within 1e-6 of each other there
bool CalcDirectionXZ(const mm::Vec3& from, const mm::Vec3& to, mm::Vec3& out);
// a random direction (each component in (-0.5, 0.5] before normalizing)
void RandomVector(mm::Vec3& out);
void RandomVectorXZ(mm::Vec3& out);
bool GetObjectTransform(const gf::GfObj* obj, mm::Vec3& out, TRANS_TYPE type);
// the trust stage's id: stages count down from 7
int CovertKizunaStageToID(int stage);
// the world position of the object's node (bone) of that name; false when it has no object or no such node
bool GetNodePosition(gf::GF_OBJ_HANDLE* handle, const char* node, mm::Vec3& out);
// the trust stage's bounds (BDAT file 51's KizunaMin and KizunaMax)
void GetKizunaMinMax(int stage, int& min, int& max);
// whether a and b are within range of each other (in the XZ plane when xz)
bool CheckInRange(const mm::Vec3& a, const mm::Vec3& b, float range, bool xz);

}  // namespace Misc

}  // namespace btl

#endif
